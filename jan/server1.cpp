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
#include <semaphore.h>
#include <pthread.h>
using namespace std;
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
						if(plansza[x][y]!=1)
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

struct Client{
	int sd=0;
	string nickname;
	int room;
};

struct Room{
	vector<Client> clients;
	vector<bool> ready;
	Game game;
};

bool close_server=false;
int serverSd;
fd_set readfds;
int max_sd;
vector<Client> clients;
int clients_size=0;
sockaddr_in newSockAddr;
socklen_t newSockAddrSize = sizeof(newSockAddr);

void terminal_inputs()
{
	while(!close_server)
	{
		string input;
		cin>>input;
		if(input=="exit"){
			close_server=true;
			continue;
		}
		cout<<"invalid input\n";
	}
	return;
}


void *client_inputs(void *arg)
{
	char msg[1500];
	while(!close_server)
	{
	FD_ZERO(&readfds);  
     
        //add master socket to set 
        FD_SET(serverSd, &readfds);  
        int max_sd = serverSd;  
    	
    	for (int i = 0 ; i < clients_size ; i++)  
        {  
            int sd = clients[i].sd;  
                 
            //if valid socket descriptor then add to read list 
            if(sd > 0)  
                FD_SET( sd , &readfds);  
                 
            //highest file descriptor number, need it for the select function 
            if(sd > max_sd)  
                max_sd = sd;  
        }  
        struct timeval tv;
        tv.tv_usec=0;
        tv.tv_sec=5;
        int activity = select( max_sd + 1 , &readfds , NULL , NULL , &tv);  
        if ((activity < 0) && (errno!=EINTR))  
        {  
            printf("select error");  
        } 
        
        
    	if (FD_ISSET(serverSd, &readfds))  
        {  
        	int sd = accept(serverSd, (sockaddr*) &newSockAddr, &newSockAddrSize);
            if (sd<0)  
            {  
                perror("accept");  
                exit(EXIT_FAILURE);  
            }  
             
            //inform user of socket number - used in send and receive commands 
            printf("New connection , socket fd is %d , ip is : %s , port : %d \n" , sd , inet_ntoa(newSockAddr.sin_addr) , ntohs(newSockAddr.sin_port));  
           
            //send new connection greeting message 
            string message = "Hello\n";
            memset(&msg, 0, sizeof(msg)); //clear the buffer
            strcpy(msg, message.c_str());
            if( send(sd, (char*)&msg, strlen(msg), 0) != strlen(msg) )  
            {  
                perror("send");  
            }  
                 
            puts("Welcome message sent successfully");  
                 
            //add new socket to array of sockets 
            bool available=false;
            for (int i = 0; i < clients_size; i++)  
            {  
                //if position is empty 
                if( clients[i].sd == 0 )  
                {  
                    clients[i].sd = sd;  
                    printf("Adding to list of clients as %d\n" , i);  
                     available=true;
                    break;  
                }  
            }  
            if(available==false){
            	Client client;
            	client.sd=sd;
            	clients.push_back(client);
            	clients_size+=1;
            	printf("Increasing list of clients and adding to list of clients as %d\n" , clients_size); 
            }
        }  
        //else its some IO operation on some other socket
        for (int i = 0; i < clients_size; i++)  
        {  
            int sd = clients[i].sd;  
                 
            if (FD_ISSET( sd , &readfds))  
            {  
                //Check if it was for closing , and also read the 
                //incoming message 
                memset(&msg, 0, sizeof(msg));//clear the buffer
                int msg_length = recv(sd, (char*)&msg, sizeof(msg), 0);
                if (msg_length== 0)  
                {  
                    //Somebody disconnected , get his details and print 
                    getpeername(sd , (sockaddr*) &newSockAddr, &newSockAddrSize);  
                    printf("Host disconnected , ip %s , port %d \n" , 
                          inet_ntoa(newSockAddr.sin_addr) , ntohs(newSockAddr.sin_port));  
                         
                    //Close the socket and mark as 0 in list for reuse 
                    close( sd );  
                    clients[i].sd = 0;  
                }  
                else 
                {   
                    cout << "Client: " << msg << endl << ">";
                    memset(&msg, 0, sizeof(msg)); //clear the buffer
                    string message;
        		getline(cin, message);
        		message+="\n";
        		strcpy(msg, message.c_str());
                    send(sd, (char*)&msg, strlen(msg), 0);
                }  
            }  
        }  
        }
        return 0;
}


void *run_games(void *arg){
	char msg[1500];
    	while(!close_server)
    	{
    		sleep(3);
    		int sd;
    		for(int i=0;i<clients_size;i++)
    		{
    		cout<<i<<"\n";
    			sd=clients[i].sd;
    			if(sd>0){
    				memset(&msg, 0, sizeof(msg)); //clear the buffer
                    		string message = "hello";
        			message+="\n";
        			strcpy(msg, message.c_str());
                    		send(sd, (char*)&msg, strlen(msg), 0);
                    }
    		}
    	}
    	return 0;
}

int main(int argc, char *argv[])
{
    //for the server, we only need to specify a port number
    if(argc != 2)
    {
        cerr << "Usage: port" << endl;
        exit(0);
    }
    //grab the port number
    int port = atoi(argv[1]);
    //buffer to send and receive messages with
     
    //setup a socket and connection tools
    sockaddr_in servAddr;
    bzero((char*)&servAddr, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(port);
 
    //open stream oriented socket with internet address
    //also keep track of the socket descriptor
    serverSd = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSd < 0)
    {
        cerr << "Error establishing the server socket" << endl;
        exit(0);
    }
    //bind the socket to its local address
    int bindStatus = bind(serverSd, (struct sockaddr*) &servAddr, 
        sizeof(servAddr));
    if(bindStatus < 0)
    {
        cerr << "Error binding socket to local address" << endl;
        exit(0);
    }
    cout << "Waiting for a client to connect..." << endl;
    //listen for up to 5 requests at a time
    listen(serverSd, 5);
    //receive a request from client using accept
    //we need a new address to connect with the client
    //accept, create a new socket descriptor to 
    //handle the new connection with client
    
    /*int newSd = accept(serverSd, (sockaddr *)&newSockAddr, &newSockAddrSize);
    if(newSd < 0)
    {
        cerr << "Error accepting request from client!" << endl;
        exit(1);
    }
    cout << "Connected with client!" << endl;
    */
    //lets keep track of the session time
    struct timeval start1, end1;
    gettimeofday(&start1, NULL);
    //also keep track of the amount of data sent as well
    pthread_t thread1;
    pthread_t thread2;
    int create_error = pthread_create(&thread1, NULL, client_inputs, NULL);
    if(!create_error)
    {
     	create_error = pthread_create(&thread2, NULL, run_games, NULL);
     	if(!create_error)
     	{
     		terminal_inputs();
     		
     		pthread_join(thread2, NULL); /*wait until the created thread terminates*/
     	}
    	pthread_join(thread1, NULL); /*wait until the created thread terminates*/
    }
    //we need to close the socket descriptors after we're all done
    gettimeofday(&end1, NULL);
    //close(newSd);
    for(int i=0;i<clients_size;i++){
    	close(clients[i].sd);
    }
    close(serverSd);
    cout << "********Session********" << endl;
    cout << "Elapsed time: " << (end1.tv_sec - start1.tv_sec) 
        << " secs" << endl;
    cout << "Connection closed..." << endl;
    return 0;   
}