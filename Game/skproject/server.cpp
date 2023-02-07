#include <iostream>
#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <fstream>
#include <vector>
#include <cmath>
#include <pthread.h>
#include <errno.h> 
using namespace std;
#define TRUE   1 
#define FALSE  0 
#define PORT 8080
//Server side
/*

g++ server.cpp -o server
./server 8080

*/
string map_files[8] = {"Maps/map1.txt","Maps/map2.txt","Maps/map3.txt","Maps/map4.txt","Maps/map5.txt","Maps/map6.txt","Maps/map7.txt","Maps/map8.txt"};
     


struct Player{
	float x,y;
	//u - up, d - down, ... , b - bomb
	char nextMove=' ';
	char looking='d';
	int hp=3;
	int bombStr=1;
	int maxBombs=1;
	int curBombs=0;
	float speed=0.05;
	int invulnerable = 0;
};

struct Bomb{
        int x,y;
        int timer=60;
        int duration=30;
        int range;
        int owner;
};

void drawGame(int** tab, int n)
{

}

struct Game{
    int n=15;
	vector<Player> gracze;
	vector<Bomb> bomby;
	int ileGraczy=0;
	int **plansza;

	void init(int k)
	{
		ifstream plik;
		plik.open(map_files[k]);
		string pom;
		plansza=new int*[n];
		for(int i=0;i<n;i++)
		{
			plik>>pom;
			plik>>pom;
			plansza[i]=new int[n];
			for(int j=0;j<n;j++)
			{
				plansza[i][j]=pom[j];
			}
		}
		plik.close();
	}


	void playerInput(int index, char input)
	{
	    gracze[index].nextMove=input;
	}

	void dodajGracza()
	{
		if(ileGraczy>=4)
		{
			return;
		}
		Player pom;
		switch(ileGraczy)
        {
        case 0:
            gracze[ileGraczy].x=1;
            gracze[ileGraczy].y=1;
            break;
        case 1:
            gracze[ileGraczy].x=n-1;
            gracze[ileGraczy].y=1;
            break;
        case 2:
            gracze[ileGraczy].x=1;
            gracze[ileGraczy].y=n-1;
            break;
        case 3:
            gracze[ileGraczy].x=n-1;
            gracze[ileGraczy].y=n-1;
            break;
        }
		gracze.push_back(pom);
		ileGraczy++;
	}
	void damagePlayer(int i, int damage)
	{
		if(gracze[i].invulnerable==0)
		{
			gracze[i].hp-=1;
			if(gracze[i].hp==0)
			{
				//TODO smierc
			}
			gracze[i].invulnerable=60;
		}
	}

    //30 ticks per second
	int tick()
	{
		//Player actions
		for(int i=0;i<ileGraczy;i++)
		{
			int y=int(gracze[i].y);
			float modY = gracze[i].y - y;
			if(modY>0.5f)
			{
				modY-=1;
				y+=1;
			}
			int x=int(gracze[i].x);
			float modX = gracze[i].x - x;
			if(modX>0.5f)
			{
				modX-=1;
				x+=1;
			}
			switch(gracze[i].nextMove)
			{
				case 'l':
					if(plansza[x][y] != 1 || (plansza[x][y] == 1 && modY <= 0)){
					gracze[i].looking='u';
					if(modX>=-10 && modX <=10 && plansza[x][y-1] ==0)
					{
						gracze[i].y-=gracze[i].speed;
					}else
					{
						if(modY>-10)
						{
							gracze[i].y-=min(modY+10, gracze[i].speed);
						}
					}
					}
					break;
				case 'r':
					gracze[i].looking='d';
					if(plansza[x][y] != 1 || (plansza[x][y] == 1 && modY >= 0)){
					if(modX>=-10 && modX <=10 && plansza[x][y+1] ==0)
					{
						gracze[i].y+=gracze[i].speed;
					}else
					{
						if(modY<10)
						{
							gracze[i].y+=min(10-modY, gracze[i].speed);
						}
					}
					}
					break;
				case 'u':
					gracze[i].looking='l';
					if(plansza[x][y] != 1 || (plansza[x][y] == 1 && modX <= 0)){
					if(modY>=-10 && modY <=10 && plansza[x-1][y] ==0)
					{
						gracze[i].x-=gracze[i].speed;
					}else
					{
						if(modX>-10)
						{
							gracze[i].x-=min(modX+10, gracze[i].speed);
						}
					}
					}
					break;
				case 'd':
					gracze[i].looking='r';
					if(plansza[x][y] != 1 || (plansza[x][y] == 1 && modX >= 0)){
					if(modY>=-10 && modY <=10 && plansza[x+1][y] ==0)
					{
						gracze[i].x+=gracze[i].speed;
					}else
					{
						if(modX<10)
						{
							gracze[i].x+=min(10-modX, gracze[i].speed);
						}
					}
					}
					break;
				case 'b':
					if(gracze[i].maxBombs>gracze[i].curBombs)
					{
						plansza[x][y]=1;
						Bomb pom;
						pom.x=x;
						pom.y=y;
						pom.range=gracze[i].bombStr;
						pom.owner=i;
						gracze[i].curBombs+=1;
						bomby.push_back(pom);
					}
					break;
			}
			if(gracze[i].invulnerable>0)gracze[i].invulnerable-=1;
			gracze[i].nextMove=' ';
		}
		//bomb ticks
		for(int i=0;i<bomby.size();i++)
		{
			if(bomby[i].timer>0)
			{
				bomby[i].timer-=1;
			}else if(bomby[i].duration >0)
			{
				bomby[i].duration -=1;
				int x=bomby[i].x;
				int y = bomby[i].y;
				int *xg=new int[ileGraczy];
				int *yg=new int[ileGraczy];
				//player coordinates
				for(int j=0;j<ileGraczy;j++)
				{
					yg[j]=int(gracze[j].y);
					float modY = gracze[j].y - yg[j];
					if(modY>0.5f)
					{
						modY-=1;
						yg[j]+=1;
					}
					xg[j]=int(gracze[j].x);
					float modX = gracze[j].x - xg[j];
					if(modX>0.5f)
					{
						modX-=1;
						xg[j]+=1;
					}
				}
				//destroy tiles and damage players
				//y+j
				for(int j=0;j<=bomby[i].range; j++)
				{
					for(int k=0;k<ileGraczy;k++)
					{
						if(xg[k] == x && yg[k] == y+j)
						{
							damagePlayer(k,1);
						}
					}
					if(plansza[x][y+j]==2)
					{
						plansza[x][y+j]=0;
					}
					if(plansza[x][y+j]==1)
					{
						break;
					}
				}
				//y-j
				for(int j=1;j<=bomby[i].range; j++)
				{
					for(int k=0;k<ileGraczy;k++)
					{
						if(xg[k] == x && yg[k] == y-j)
						{
							damagePlayer(k,1);
						}
					}
					if(plansza[x][y-j]==2)
					{
						plansza[x][y-j]=0;
					}
					if(plansza[x][y-j]==1)
					{
						break;
					}
				}
				//x+j
				for(int j=1;j<=bomby[i].range; j++)
				{
					for(int k=0;k<ileGraczy;k++)
					{
						if(xg[k] == x+j && yg[k] == y)
						{
							damagePlayer(k,1);
						}
					}
					if(plansza[x+j][y]==2)
					{
						plansza[x+j][y]=0;
					}
					if(plansza[x+1][y]==1)
					{
						break;
					}
				}
				//x-j
				for(int j=1;j<=bomby[i].range; j++)
				{
					for(int k=0;k<ileGraczy;k++)
					{
						if(xg[k] == x-j && yg[k] == y)
						{
							damagePlayer(k,1);
						}
					}
					if(plansza[x-j][y]==2)
					{
						plansza[x-j][y]=0;
					}
					if(plansza[x-1][y]==1)
					{
						break;
					}
				}
			}else
			{
				plansza[bomby[i].x][bomby[i].y]=0;
				gracze[bomby[i].owner].curBombs-=1;
				bomby.erase(bomby.begin()+i);
				i-=1;
			}
		}
        	return 0;
	}
	
	string drawGame()
	{
		int ile=0;
		string send ="";
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				if(plansza[i][j]==2)
				{
					ile++;
					send+=to_string(i)+";"+to_string(j)+";";
				}
			}
		}
		send = to_string(ile)+";"+send;
		string undetonated = "";
		string detonated = "";
		int und=0;
		int det=0;
		for(int i=0;i<bomby.size();i++)
		{
			if(bomby[i].timer>0)
			{
				und+=1;
				undetonated+=to_string(bomby[i].x)+";"+to_string(bomby[i].y)+";";
			}else
			{
				det+=1;
				detonated+=to_string(bomby[i].x)+";"+to_string(bomby[i].y)+";"+to_string(bomby[i].range)+";";
			}
		}
		send+=to_string(und)+";"+undetonated+to_string(det)+";"+detonated;
		send+=to_string(ileGraczy)+";";
		for(int i=0;i<ileGraczy;i++)
		{
			int x=gracze[i].x*100;
			int y=gracze[i].y*100;
			send+=to_string(x)+";"+to_string(y)+";";
			send+=gracze[i].looking+";";
			send+=to_string(gracze[i].hp)+";";
			send+=to_string(gracze[i].bombStr)+";";
			send+=to_string(gracze[i].maxBombs)+";";
			send+=to_string(gracze[i].curBombs)+";";
			if(gracze[i].invulnerable>0)
			{
				send+="1;";
			}else
			{
				send+="0;";
			}
		}
		return send;
	}
};


int main(int argc , char *argv[])  
{  
    int opt = 1,  max_clients = 100, client_socket[100];  
    int master_socket, addrlen, new_socket, activity, i, valread, sd, max_sd;  
    struct sockaddr_in address;  
    char buffer[1500]; 
    //set of socket descriptors 
    fd_set readfds;  
    //a message 
    std::string s = "ECHO Daemon v1.0 \r\n";
    char *message = &s[0];  
     
    //initialise all client_socket[] to 0 so not checked 
    for (i = 0; i < max_clients; i++)  
    {  
        client_socket[i] = 0;  
    }  
         
    //create a master socket 
    if( (master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)  
    {  
        perror("socket failed");  
        exit(EXIT_FAILURE);  
    }  
     
    //set master socket to allow multiple connections , 
    //this is just a good habit, it will work without this 
    if( setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, 
          sizeof(opt)) < 0 )  
    {  
        perror("setsockopt");  
        exit(EXIT_FAILURE);  
    }  
     
    //type of socket created 
    address.sin_family = AF_INET;  
    address.sin_addr.s_addr = INADDR_ANY;  
    address.sin_port = htons( PORT );  
         
    //bind the socket to localhost port 8888 
    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0)  
    {  
        perror("bind failed");  
        exit(EXIT_FAILURE);  
    }  
    printf("Listener on port %d \n", PORT);  
         
    //try to specify maximum of 3 pending connections for the master socket 
    if (listen(master_socket, 3) < 0)  
    {  
        perror("listen");  
        exit(EXIT_FAILURE);  
    }  
         
    //accept the incoming connection 
    addrlen = sizeof(address);  
    puts("Waiting for connections ...");  
         
    while(TRUE)  
    {  
        //clear the socket set 
        FD_ZERO(&readfds);  
     
        //add master socket to set 
        FD_SET(master_socket, &readfds);  
        max_sd = master_socket;  
             
        //add child sockets to set 
        for ( i = 0 ; i < max_clients ; i++)  
        {  
            //socket descriptor 
            sd = client_socket[i];  
                 
            //if valid socket descriptor then add to read list 
            if(sd > 0)  
                FD_SET( sd , &readfds);  
                 
            //highest file descriptor number, need it for the select function 
            if(sd > max_sd)  
                max_sd = sd;  
        }  
     
        //wait for an activity on one of the sockets , timeout is NULL , 
        //so wait indefinitely 
        activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);  
       
        if ((activity < 0) && (errno!=EINTR))  
        {  
            printf("select error");  
        }  
             
        //If something happened on the master socket , 
        //then its an incoming connection 
        if (FD_ISSET(master_socket, &readfds))  
        {  
            if ((new_socket = accept(master_socket, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)	{ perror("accept"); exit(EXIT_FAILURE); }  
             
            //inform user of socket number - used in send and receive commands 
            printf("New connection, socket fd is %d, ip is : %s, port : %d \n", new_socket, inet_ntoa(address.sin_addr), ntohs(address.sin_port));  
           
            //send new connection greeting message 
            if( send(new_socket, message, strlen(message), 0) != strlen(message) )		{ perror("send"); }  
                 
            puts("Welcome message sent successfully");  
                 
            //add new socket to array of sockets 
            for (i = 0; i < max_clients; i++)  
            {  
                //if position is empty 
                if( client_socket[i] == 0 )  
                {  
                    client_socket[i] = new_socket;  
                    printf("Adding to list of sockets as %d\n" , i);  
                         
                    break;  
                }  
            }  
        }  
             
        //else its some IO operation on some other socket
        for (i = 0; i < max_clients; i++)  
        {  
            sd = client_socket[i];  
			
            if (FD_ISSET( sd , &readfds))  
            {  
                //Check if it was for closing , and also read the 
                //incoming message 
				
                if ((valread = read( sd , buffer, 1024)) == 0)  
                {  
					printf(valread);  
                    //Somebody disconnected , get his details and print 
                    getpeername(sd , (struct sockaddr*)&address, (socklen_t*)&addrlen);  
                    printf("Host disconnected , ip %s , port %d \n" , 
                          inet_ntoa(address.sin_addr) , ntohs(address.sin_port));  
                         
                    //Close the socket and mark as 0 in list for reuse 
                    close( sd );  
                    client_socket[i] = 0;  
                }  
                     
                //Echo back the message that came in 
                else 
                {  
                    //set the string terminating NULL byte on the end 
                    //of the data read 
                    buffer[valread] = '\0';  

                    send(sd , buffer , strlen(buffer) , 0 );  
                }  
            }  
        }  
    }  
         
    return 0;  
}  




// int main(int argc, char *argv[])
// {
//     char msg[1500];                                             // buffer to send and receive messages with
//     sockaddr_in servAddr;
//     sockaddr_in newSockAddr;
//     socklen_t newSockAddrSize = sizeof(newSockAddr);
//     struct timeval start1, end1;

//     if(argc != 2) { cerr << "Usage: port" << endl; exit(0); }
//     int port = atoi(argv[1]);                                   // grab the port number
    
//     bzero((char*)&servAddr, sizeof(servAddr));					//setup a socket and connection tools
//     servAddr.sin_family = AF_INET;
//     servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
//     servAddr.sin_port = htons(port);
 
//     int serverSd = socket(AF_INET, SOCK_STREAM, 0);
//     if(serverSd < 0) { cerr << "Error establishing the server socket" << endl; exit(0); }
//     int bindStatus = bind(serverSd, (struct sockaddr*)&servAddr, sizeof(servAddr));	
//     if(bindStatus < 0) { cerr << "Error binding socket to local address" << endl; exit(0); }
//     cout << "Waiting for connect..." << endl;

//     listen(serverSd, 5);    									//listen for up to 5 requests at a time, suggestion

//     int newSd = accept(serverSd, (sockaddr *)&newSockAddr, &newSockAddrSize); //wiecej acceptów żeby przyjac klientów, powinno byc w petli

//     if(newSd < 0) {
//         cerr << "Error accepting request from client!" << endl;
//         exit(1);
//     }
//     cout << "Connected with client!" << endl;
// 	int newSd2 = accept(serverSd, (sockaddr *)&newSockAddr, &newSockAddrSize); //wiecej acceptów żeby przyjac klientów, powinno byc w petli
//     if(newSd2 < 0) {
//         cerr << "Error accepting request from client2!" << endl;
//         exit(1);
//     }
//     cout << "Connected with client2!" << endl;

//     // gettimeofday(&start1, NULL);
//     //also keep track of the amount of data sent as well
//     int bytesRead, bytesWritten = 0;
//     while(1)
//     {
//         //receive a message from the client (listen)
//         cout << "Awaiting client response..." << endl;
//         memset(&msg, 0, sizeof(msg));                                   //clear the buffer
//         bytesRead += recv(newSd, (char*)&msg, sizeof(msg), 0);
//         if(!strcmp(msg, "exit"))
//         {
//             cout << "Client has quit the session" << endl;
//             break;
//         }
//         cout << "Client: " << msg << endl;
//         cout << ">";
//         string data;
//         getline(cin, data);
//         memset(&msg, 0, sizeof(msg));                                   //clear the buffer
//         strcpy(msg, data.c_str());
//         if(data == "exit") {
//             send(newSd, (char*)&msg, strlen(msg), 0);            //send to the client that server has closed the connection
//             break;
//         }
//         //send the message to client
//         bytesWritten += send(newSd, (char*)&msg, strlen(msg), 0);
//     }
//     //we need to close the socket descriptors after we're all done
//     // gettimeofday(&end1, NULL);
//     close(newSd);
//     close(serverSd);
//     // cout << "********Session********" << endl;
//     // cout << "Bytes written: " << bytesWritten << " Bytes read: " << bytesRead << endl;
//     // cout << "Elapsed time: " << (end1.tv_sec - start1.tv_sec) 
//     //     << " secs" << endl;
//     cout << "Connection closed..." << endl;
//     return 0;   
// }
