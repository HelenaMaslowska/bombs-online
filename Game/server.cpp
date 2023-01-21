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
using namespace std;
//Server side
/*

g++ server.cpp -o server
./server 8080

*/
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

	void init()
	{
		plansza=new int*[n];
		for(int i=0;i<n;i++)
		{
			plansza[i]=new int[n];
		}
		//TODO zaladuj plansze
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
				case 'u':
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
				case 'd':
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
				case 'l':
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
				case 'r':
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
						break;
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
						break;
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
						break;
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
						break;
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
};

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
    char msg[1500];
     
    //setup a socket and connection tools
    sockaddr_in servAddr;
    bzero((char*)&servAddr, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(port);
 
    //open stream oriented socket with internet address
    //also keep track of the socket descriptor
    int serverSd = socket(AF_INET, SOCK_STREAM, 0);
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
    sockaddr_in newSockAddr;
    socklen_t newSockAddrSize = sizeof(newSockAddr);
    //accept, create a new socket descriptor to 
    //handle the new connection with client
    int newSd = accept(serverSd, (sockaddr *)&newSockAddr, &newSockAddrSize);
    if(newSd < 0)
    {
        cerr << "Error accepting request from client!" << endl;
        exit(1);
    }
    cout << "Connected with client!" << endl;
    //lets keep track of the session time
    struct timeval start1, end1;
    gettimeofday(&start1, NULL);
    //also keep track of the amount of data sent as well
    int bytesRead, bytesWritten = 0;
    while(1)
    {
        //receive a message from the client (listen)
        cout << "Awaiting client response..." << endl;
        memset(&msg, 0, sizeof(msg));//clear the buffer
        bytesRead += recv(newSd, (char*)&msg, sizeof(msg), 0);
        if(!strcmp(msg, "exit"))
        {
            cout << "Client has quit the session" << endl;
            break;
        }
        cout << "Client: " << msg << endl;
        cout << ">";
        string data;
        getline(cin, data);
        memset(&msg, 0, sizeof(msg)); //clear the buffer
        strcpy(msg, data.c_str());
        if(data == "exit")
        {
            //send to the client that server has closed the connection
            send(newSd, (char*)&msg, strlen(msg), 0);
            break;
        }
        //send the message to client
        bytesWritten += send(newSd, (char*)&msg, strlen(msg), 0);
    }
    //we need to close the socket descriptors after we're all done
    gettimeofday(&end1, NULL);
    close(newSd);
    close(serverSd);
    cout << "********Session********" << endl;
    cout << "Bytes written: " << bytesWritten << " Bytes read: " << bytesRead << endl;
    cout << "Elapsed time: " << (end1.tv_sec - start1.tv_sec) 
        << " secs" << endl;
    cout << "Connection closed..." << endl;
    return 0;   
}
