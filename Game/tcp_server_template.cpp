#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <error.h>
#include <netdb.h>
#include <sys/epoll.h>
#include <poll.h>
#include <thread>
#include <unordered_set>
#include <signal.h>
#include<iostream>
#include<vector>
#include<fstream>

struct Player{
	int x,y;
	//u - up, d - down, ... , b - bomb
	char nextMove=' ';
	char looking='d';
	int hp=3;
	int bombStr=3;
	int maxBombs=1;
	int curBombs=0;
	float speed=1;
};

struct Bomb{
        int x,y;
        int timer=60;
        int range;
};

void drawGame(int** tab, int n)
{

}

struct Game{
    int n=15;
	std::vector<Player> gracze;
	int ileGraczy=0;
	int **plansza;

	void init()
	{
		plansza = new int*[n];
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

    //30 ticks per second
	void tick()
	{
		//TODO player actions

		//TODO bomb ticks

		//drawGame(screen,n);
		//Clear inputs
		for(int i=0;i<ileGraczy;i++)
        {
            gracze[i].nextMove=' ';
        }
	}
};

// server socket
int servFd;

// client sockets
std::unordered_set<int> clientFds;

// handles SIGINT
void ctrl_c(int);

// sends data to clientFds excluding fd
void sendToAllBut(int fd, char * buffer, int count);

// converts cstring to port
uint16_t readPort(char * txt);

// sets SO_REUSEADDR
void setReuseAddr(int sock);

int main(int argc, char ** argv){
	// get and validate port number
	if(argc != 2) error(1, 0, "Need 1 arg (port)");
	auto port = readPort(argv[1]);

	// create socket
	servFd = socket(AF_INET, SOCK_STREAM, 0);
	if(servFd == -1) error(1, errno, "socket failed");

	// graceful ctrl+c exit
	signal(SIGINT, ctrl_c);
	// prevent dead sockets from throwing pipe errors on write
	signal(SIGPIPE, SIG_IGN);

	setReuseAddr(servFd);

	// bind to any address and port provided in arguments
	sockaddr_in serverAddr{.sin_family=AF_INET, .sin_port=htons((short)port), .sin_addr={INADDR_ANY}};
	int res = bind(servFd, (sockaddr*) &serverAddr, sizeof(serverAddr));
	if(res) error(1, errno, "bind failed");

	// enter listening mode
	res = listen(servFd, 1);
	if(res) error(1, errno, "listen failed");

/****************************/

	while(true){
		// prepare placeholders for client address
		sockaddr_in clientAddr{0};
		socklen_t clientAddrSize = sizeof(clientAddr);

		// accept new connection
		auto clientFd = accept(servFd, (sockaddr*) &clientAddr, &clientAddrSize);
		if(clientFd == -1) error(1, errno, "accept failed");

		// add client to all clients set
		clientFds.insert(clientFd);

		// tell who has connected
		printf("new connection from: %s:%hu (fd: %d)\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port), clientFd);

/****************************/

		// read a message
		char buffer[255];
		int count = read(clientFd, buffer, 255);

		if(count < 1) {
			printf("removing %d\n", clientFd);
			clientFds.erase(clientFd);
			close(clientFd);
			continue;
		} else {
			// broadcast the message
			sendToAllBut(clientFd, buffer, count);
		}

	}

/****************************/
}

uint16_t readPort(char * txt){
	char * ptr;
	auto port = strtol(txt, &ptr, 10);
	if(*ptr!=0 || port<1 || (port>((1<<16)-1))) error(1,0,"illegal argument %s", txt);
	return port;
}

void setReuseAddr(int sock){
	const int one = 1;
	int res = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
	if(res) error(1,errno, "setsockopt failed");
}

void ctrl_c(int){
	for(int clientFd : clientFds)
		close(clientFd);
	close(servFd);
	printf("Closing server\n");
	exit(0);
}

void sendToAllBut(int fd, char * buffer, int count){
	int res;
	decltype(clientFds) bad;
	for(int clientFd : clientFds){
		if(clientFd == fd) continue;
		res = write(clientFd, buffer, count);
		if(res!=count)
			bad.insert(clientFd);
	}
	for(int clientFd : bad){
		printf("removing %d\n", clientFd);
		clientFds.erase(clientFd);
		close(clientFd);
	}
}
