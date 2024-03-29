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
#include <ctime>
#include <time.h>
#include <chrono>
using namespace std;

//Server side
/*

g++ server.cpp -o server
./server 8080

*/

string map_files[4] = {"Maps/map1.txt","Maps/map2.txt","Maps/map3.txt","Maps/map4.txt"};



struct Player{
	float x,y;
	//u - up, d - down, ... , b - bomb
	string next_move="";
	string looking="d";
	int hp=3;
	int bombStr=1;
	int maxBombs=1;
	int curBombs=0;
	float speed=0.05;
	int invulnerable = 0;
};

struct Bomb{
        int x,y;
        int timer=90;
        int duration=60;
        int range;
        int owner;
};

struct Powerup{
	int x;
	int y;
	int type;
	int owner=-1;
	int duration=300;
};

void drawGame(int** tab, int n)
{

}

struct Game{
    int n=15;
	vector<Player> gracze;
	vector<Bomb> bomby;
	vector<Powerup> powerups;
	int ileGraczy=0;
	int **plansza;
	int who_won=-1;
	void init(int k)
	{
		ifstream plik;
		plik.open(map_files[k]);
		string pom;
		plansza=new int*[n];
		for(int i=0;i<n;i++)
		{
			plik>>pom;
			plansza[i]=new int[n];
			for(int j=0;j<n;j++)
			{

				plansza[i][j]=pom[j]-48;
				//cout<<plansza[i][j];
			}
			//cout<<"\n";
		}
		plik.close();

	}


	void player_input(int index, char input)
	{
		if(index<ileGraczy)
		{
			gracze[index].next_move=input;
		}
	}

	void remove_player(int index)
        {
        	if(index<ileGraczy)
        	{
        		gracze.erase(gracze.begin()+index);
        		ileGraczy-=1;
        		for(int i=0;i<bomby.size();i++)
        		{
        			if(bomby[i].owner==index)
        			{
        				bomby[i].owner=-1;
        			}
        			if(bomby[i].owner>index)
        			{
        				bomby[i].owner-=1;
        			}
        		}
        		for(int i=0;i<powerups.size();i++)
        		{
        			if(powerups[i].owner==index)
        			{
        				bomby[i].owner=-1;
        			}
        			if(powerups[i].owner>index)
        			{
        				bomby[i].owner-=1;
        			}
        		}
        	}
        }

	void add_player()
	{
		if(ileGraczy>=4)
		{
			return;
		}
		Player temp_player;
		switch(ileGraczy)
        {
        case 0:
            temp_player.x=1;
            temp_player.y=1;
            break;
        case 1:
            temp_player.x=n-2;
            temp_player.y=1;
            break;
        case 2:
            temp_player.x=1;
            temp_player.y=n-2;
            break;
        case 3:
            temp_player.x=n-2;
            temp_player.y=n-2;
            break;
        }
		gracze.push_back(temp_player);
		ileGraczy++;
	}
	void damagePlayer(int i, int damage)
	{
		if(gracze[i].invulnerable==0)
		{
			gracze[i].hp-=1;
			if(gracze[i].hp==0)
			{
				gracze[i].x=100;
				gracze[i].y=100;
			}
			gracze[i].invulnerable=60;
		}
	}
	void destroy_wall(int x, int y)
	{
		plansza[x][y]=0;
		int powerup_generation=(rand()%3);
		if(powerup_generation==0)
		{
			Powerup temp_powerup;
			temp_powerup.x=x;
			temp_powerup.y=y;
			temp_powerup.type=(rand()%5)+1;
			powerups.push_back(temp_powerup);
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
			if(gracze[i].hp>0)
			{
			if(gracze[i].next_move=="l"){
					if(plansza[x][y] ==0 || (plansza[x][y] >0 && modY <= 0)){
					gracze[i].looking="l";
					if(modX+0.1f>=-0.001f && modX -0.1f<=0.001f && plansza[x][y-1] ==0)
					{
						gracze[i].y-=gracze[i].speed;

					}else
					{
						if(modY>-0.1f)
						{
							gracze[i].y-=gracze[i].speed;
							if(gracze[i].y<float(y)-0.10f)
							{
								gracze[i].y=float(y)-0.10f;
							}
						}
					}
					}
			}
			if(gracze[i].next_move=="r"){
					gracze[i].looking="r";
					if(plansza[x][y] ==0 || (plansza[x][y] >0 && modY >= 0)){
					if(modX+0.1f>=-0.001f && modX -0.1f<=0.001f && plansza[x][y+1] ==0)
					{
						gracze[i].y+=gracze[i].speed;
					}else
					{
						if(modY<0.1f)
						{
							gracze[i].y+=gracze[i].speed;
							if(gracze[i].y>float(y)+0.10f)
							{
								gracze[i].y=float(y)+0.10f;
							}
						}
					}
					}
			}
			if(gracze[i].next_move=="u"){
					gracze[i].looking="u";
					if(plansza[x][y] ==0 || (plansza[x][y] >0 && modX <= 0)){
					if(modY+0.1f>=-0.001f && modY -0.1f<=0.001f && plansza[x-1][y] ==0)
					{
						gracze[i].x-=gracze[i].speed;
					}else
					{
						if(modX>-0.1f)
						{
							gracze[i].x-=gracze[i].speed;
							if(gracze[i].x<float(x)-0.10f)
							{
								gracze[i].x=float(x)-0.10f;
							}
						}
					}
					}
			}
			if(gracze[i].next_move=="d"){
					gracze[i].looking="d";
					if(plansza[x][y] ==0 || (plansza[x][y] >0 && modX >= 0)){
					if(modY+0.1f>=-0.001f && modY -0.1f<=0.001f && plansza[x+1][y] ==0)
					{
						gracze[i].x+=gracze[i].speed;
					}else
					{
						if(modX<0.1f)
						{

							gracze[i].x+=gracze[i].speed;
							if(gracze[i].x>float(x)+0.10f)
							{
								gracze[i].x=float(x)+0.10f;
							}
						}
					}
					}
			}
			if(gracze[i].next_move=="b"){
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
			}
			}
			if(gracze[i].invulnerable>0)gracze[i].invulnerable-=1;
			gracze[i].next_move="";
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
				for(int k=0;k<ileGraczy;k++)
				{
					if(xg[k] == x && yg[k] == y)
					{
						damagePlayer(k,1);
					}
				}
				//y+j
				for(int j=1;j<=bomby[i].range; j++)
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
						destroy_wall(x,y+j);
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
						destroy_wall(x,y-j);
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
						destroy_wall(x+j,y);
					}
					if(plansza[x+j][y]==1)
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
						destroy_wall(x-j,y);
					}
					if(plansza[x-j][y]==1)
					{
						break;
					}
				}
			}else
			{
				plansza[bomby[i].x][bomby[i].y]=0;
				if(bomby[i].owner!=-1) gracze[bomby[i].owner].curBombs-=1;
				bomby.erase(bomby.begin()+i);
				i-=1;
			}
		}
		for(int i=0;i<powerups.size();i++)
		{
			if(powerups[i].x!=-1)
			{
				for(int j=0;j<ileGraczy;j++)
				{
					int x,y;
					y=int(gracze[j].y);
					float modY = gracze[j].y - y;
					if(modY>0.5f)
					{
						modY-=1;
						y+=1;
					}
					x=int(gracze[j].x);
					float modX = gracze[j].x - x;
					if(modX>0.5f)
					{
						modX-=1;
						x+=1;
					}
					if(powerups[i].x==x && powerups[i].y==y)
					{
						switch(powerups[i].type)
						{
							case 1:
								gracze[j].bombStr+=1;
								powerups.erase(powerups.begin()+i);
								i--;
								break;
							case 2:
								gracze[j].maxBombs+=1;
								powerups.erase(powerups.begin()+i);
								i--;
								break;
							case 3:
								gracze[j].speed+=0.05;
								powerups[i].x=-1;
								powerups[i].y=-1;
								powerups[i].owner=j;
								break;
							case 4:
								gracze[j].hp+=1;
								powerups.erase(powerups.begin()+i);
								i--;
								break;
							case 5:
								gracze[j].invulnerable+=300;
								powerups.erase(powerups.begin()+i);
								i--;
								break;
						}
						break;
					}
				}
			}else
			{
				if(powerups[i].duration>0)
				{
					powerups[i].duration-=1;
				}else
				{
					if(powerups[i].owner!=-1)
					{
						int owner=powerups[i].owner;
						gracze[owner].speed-=0.05;
					}
					powerups.erase(powerups.begin()+i);
					i--;
				}
			}
		}
		if(who_won==-1)
		{
			int alive_players=0;;
			for(int i=0;i<ileGraczy;i++)
			{
				if(gracze[i].hp>0)
				{
					alive_players+=1;
				}
			}
			if(alive_players<=1)
			{
				for(int i=0;i<ileGraczy;i++)
				{
					if(gracze[i].hp>0)
					{
						who_won=i;
					}
				}
				if(who_won==-1)who_won=4;
			}
		}else
		{
			who_won=-2;
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
		send = ";game;"+to_string(ile)+";"+send;
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
		string powerup_string="";
		int powerup_number=0;
		for(int i=0;i<powerups.size();i++)
		{
			if(powerups[i].x!=-1)
			{
				powerup_number+=1;
				powerup_string+=to_string(powerups[i].x)+";";
				powerup_string+=to_string(powerups[i].y)+";";
				powerup_string+=to_string(powerups[i].type)+";";
			}
		}
		send+=to_string(powerup_number)+";"+powerup_string;
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
	int room=-1;
};

struct Room{
	vector<int> clients;
	vector<bool> ready;
	Game game;
	int map;
	bool all_ready=false;
};

bool close_server=false;
int serverSd;
fd_set readfds;
int max_sd;
vector<Client> clients;
vector<Room> rooms;
vector<struct timeval> game_timers;
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
		if(input=="clients"){
			for(int i=0;i<clients_size;i++)
			{
				cout<<"sd: "<<clients[i].sd<<", nickname: "<<clients[i].nickname<<", room: "<<clients[i].room<<"\n";
			}
			continue;
		}
		cout<<"invalid input\n";
	}
	return;
}

void send_message(int sd, string message){
	//cout<<sd<<": "<<message<<"\n";
	char msg[1500];
	memset(&msg, 0, sizeof(msg));
	message = "!" + message + "?";
	strcpy(msg, message.c_str());
	int send_size = send(sd, (char*)&msg, strlen(msg), 0);
	if(send_size != strlen(msg))
	{
		cout<<"error sending message '" + message + "'\n"<<"wanted to send: "<<strlen(msg)<<"\nsent: "<<send_size<<"\n";
		char buffer[ 256 ];
		 char * errorMsg = strerror_r( errno, buffer, 256 );
    		printf("Error %s\n", errorMsg);
	}
}

void send_room_info(int room_id)
{
	Room room=rooms[room_id];
	string response=";nicks;";
	for(int i=0;i<4;i++)
	{
		if(room.clients.size()>i)
		{
			response+=clients[room.clients[i]].nickname;
		}
		response+=";";
	}
	for(int i=0;i<4;i++)
	{
		if(room.clients.size()>i)
		{
			response+=to_string(room.ready[i]);
		}else
		{
			response+="0";
		}
		response+=";";
	}
	for(int i=0;i<room.clients.size();i++)
	{
		send_message(clients[room.clients[i]].sd,response);
	}
}


void *client_inputs(void *arg)
{
	char msg[1500];
	while(!close_server)
	{
	FD_ZERO(&readfds);

        FD_SET(serverSd, &readfds);
        int max_sd = serverSd;

    	for (int i = 0 ; i < clients_size ; i++)
        {
            int sd = clients[i].sd;

            if(sd > 0)
                FD_SET( sd , &readfds);

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
             int option=1;
    		setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
            printf("New connection , socket fd is %d , ip is : %s , port : %d \n" , sd , inet_ntoa(newSockAddr.sin_addr) , ntohs(newSockAddr.sin_port));

            bool available=false;
            for (int i = 0; i < clients_size; i++)
            {
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
            	printf("Increasing list of clients and adding to list of clients as %d\n" , clients_size-1);
            }
        }
        for (int i = 0; i < clients_size; i++)
        {
            int sd = clients[i].sd;

            if (FD_ISSET( sd , &readfds))
            {
                memset(&msg, 0, sizeof(msg));
                int msg_length = recv(sd, (char*)&msg, sizeof(msg), 0);
                if (msg_length== 0)
                {
                	int room_id=clients[i].room;
                	if(room_id>=0)
                	{
                		for(int j=0;j<rooms[room_id].clients.size();j++)
                		{
                			if(rooms[room_id].clients[j]==i)
                			{
                				rooms[room_id].clients.erase(rooms[room_id].clients.begin()+j);
                				rooms[room_id].ready.erase(rooms[room_id].ready.begin()+j);
                				if(rooms[room_id].all_ready==true)
                				{
                					rooms[room_id].game.remove_player(j);
                				}
                				break;
                			}
                		}
                		send_room_info(room_id);
                	}
                    getpeername(sd , (sockaddr*) &newSockAddr, &newSockAddrSize);
                    printf("Host disconnected , ip %s , port %d \n" ,
                          inet_ntoa(newSockAddr.sin_addr) , ntohs(newSockAddr.sin_port));

                    close( sd );
                    clients[i].sd = 0;
                    clients[i].nickname="";
                    clients[i].room=-1;
                }
                else if(msg_length>0)
                {
                	string message = msg;
                	vector<string> messages;
                	string temp_msg="";
                	for(int j=0;j<message.length();j++)
                	{
                		if(message[j]=='!')
                		{
                			temp_msg="!";
                			continue;
                		}
                		if(message[j]=='?')
                		{
                			temp_msg+="?";
                			messages.push_back(temp_msg);
                			temp_msg="";
                			continue;
                		}
                		temp_msg+=message[j];
                	}
                	for(int k=0;k<messages.size();k++)
                	{
                	message=messages[k];
                	vector<string> parsed_message;
                	int parsed_size=0;
                	string temp="";
                	for(int j=0;j<message.size();j++)
                	{
                		if(message[j]==';')
                		{
                			parsed_message.push_back(temp);
                			temp="";
                			parsed_size+=1;
                		}else
                		{
                			temp+=message[j];
                		}
                	}
                	temp=temp[0];
                	parsed_message.push_back(temp);
                	parsed_size+=1;
                	for(int j=0;j<parsed_size;j++)
                	{
                		cout<<parsed_message[j]+" ";
                	}
                	cout<<"\n";
                	if(parsed_message[0]=="!" && (parsed_message[parsed_size-1]=="?" || parsed_message[parsed_size-1]=="?\n" ))
                	{
                		bool handled=false;
                		if(parsed_message[1]=="nick")
                		{
                			handled=true;
                			if(parsed_size !=4)
                			{
                				cout<<"Invalid nick command length\n";
                				cout<<message<<"\n";
                			}else
                			{
                				clients[i].nickname=parsed_message[2];
                				bool empty_room=false;
                				for(int j=0;j<rooms.size();j++)
                				{
                					if(rooms[j].clients.size()<4)
                					{
                						if(rooms[j].all_ready==false)
                						{
                							empty_room=true;
                							clients[i].room=j;
                							rooms[j].clients.push_back(i);
                							rooms[j].ready.push_back(0);
                						}
                					}
                				}
                				if(!empty_room)
                				{
                					Room temp_room;
                					Game temp_game;
                					temp_room.game=temp_game;
                					temp_room.map=(rand()%4);
                					temp_room.game.init(temp_room.map);
                					temp_room.clients.push_back(i);
                					temp_room.ready.push_back(0);
                					rooms.push_back(temp_room);
                					clients[i].room=rooms.size()-1;
                					struct timeval now;
                					gettimeofday(&now, NULL);
                					game_timers.push_back(now);
                				}
                				send_room_info(clients[i].room);
                				message=";map;"+to_string(rooms[clients[i].room].map)+";";
                				send_message(sd,message);
                			}
                		}
                		if(parsed_message[1]=="rdy")
                		{
                			handled=true;
                			if(parsed_size !=4)
                			{
                				cout<<"Invalid ready command length\n";
                				cout<<message<<"\n";
                			}else
                			{
                				int room_id=clients[i].room;
                				if(room_id!=-1)
                				{
                					int ready_id;
                					for(int j=0;j<rooms[room_id].clients.size();j++)
                					{
                						if(rooms[room_id].clients[j]==i)
                						{
                							ready_id=j;
                							break;
                						}
                					}
                					try
                					{
                						int state = atoi(parsed_message[2].c_str());
                						rooms[room_id].ready[ready_id]=state;
                						send_room_info(clients[i].room);
                					}catch(const exception& e)
                					{
                						cout<<"Ready state is not a number\n";
                					}
                				}
                			}
                		}
                		if(parsed_message[1]=="go")
                		{
                			handled=true;
                			if(parsed_size !=4)
                			{
                				cout<<"Invalid player command length\n";
                				cout<<message<<"\n";
                			}else
                			{
                				int room_id=clients[i].room;
                				if(room_id!=-1)
                				{
                					int player_id;
                					for(int j=0;j<rooms[room_id].clients.size();j++)
                					{
                						if(rooms[room_id].clients[j]==i)
                						{
                							player_id=j;
                							break;
                						}
                					}
                					rooms[room_id].game.player_input(player_id,parsed_message[2][0]);
                				}

                			}
                		}
                		if(parsed_message[1]=="exit")
                		{
                			handled=true;
                			if(parsed_size !=3)
                			{
                				cout<<"Invalid exit command length\n";
                				cout<<message<<"\n";
                			}else
                			{
                				int room_id=clients[i].room;
                				if(room_id!=-1){
                					int player_id;
                					for(int j=0;j<rooms[room_id].clients.size();j++)
                					{
                						if(rooms[room_id].clients[j]==i)
                						{
                							rooms[room_id].clients.erase(rooms[room_id].clients.begin()+j);
                							rooms[room_id].ready.erase(rooms[room_id].ready.begin()+j);
                							if(rooms[room_id].all_ready==true)
                							{
                								rooms[room_id].game.remove_player(j);
                							}
                							break;
                						}
                					}
                					clients[i].room=-1;
                					send_room_info(room_id);
                				}

                			}
                		}
                		if(!handled)
                		{
                			cout<<"Recieved invalid command in message\n";
                		}
                	}else
                	{
                		cout<<"Recieved invalid message\n";
                	}
                	}
                }  else
                {
                	cout<<"Error recieving message\n";
                }
            }
        }
        }
        return 0;
}


void *run_games(void *arg){
    	while(!close_server)
    	{
    		for(int i=0;i<rooms.size();i++)
    		{
    			if(rooms[i].all_ready==false)
    			{
    				int sum=0;
    				for(int j=0;j<rooms[i].ready.size();j++)
    				{
    					sum+=rooms[i].ready[j];
    				}
    				if(sum==rooms[i].ready.size() && sum>=2)
    				{
    					rooms[i].all_ready=true;
    					for(int j=0;j<rooms[i].clients.size();j++)
    					{
    						send_message(clients[rooms[i].clients[j]].sd,";allrdy;");
    						rooms[i].game.add_player();
    					}
    				}
    			}

    			if(rooms[i].all_ready==true)
    			{
    				struct timeval now;
				gettimeofday(&now, NULL);
				unsigned long long difference = (now.tv_sec*1000 + now.tv_usec/1000) - (game_timers[i].tv_sec*1000 + game_timers[i].tv_usec/1000);
				//cout<<difference<<"\n";
    				if(difference >= 1000/30)
    				{
    					rooms[i].game.tick();
    					string game_state=rooms[i].game.drawGame();
    					for(int j=0;j<rooms[i].clients.size();j++)
    					{
    						int sd=clients[rooms[i].clients[j]].sd;
    						send_message(sd,game_state);
    						if(rooms[i].game.who_won==j)
    						{
    							send_message(sd,";win;");
    						}else if(rooms[i].game.who_won>=0)
    						{
    							send_message(sd,";lose;");
    						}
    					}
    					game_timers[i]=now;

    				}
    				if(rooms[i].clients.size()==0)
    				{
    					Game temp_game;
    					rooms[i].game=temp_game;
    					rooms[i].all_ready=false;
    					rooms[i].map=(rand()%4);
    					rooms[i].game.init(rooms[i].map);
    				}
    			}
    		}
    	}
    	return 0;
}

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        cerr << "Usage: port" << endl;
        exit(0);
    }
    int port = atoi(argv[1]);

    sockaddr_in servAddr;
    bzero((char*)&servAddr, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(port);

    serverSd = socket(AF_INET, SOCK_STREAM, 0);
    int option=1;
    setsockopt(serverSd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
    if(serverSd < 0)
    {
        cerr << "Error establishing the server socket" << endl;
        exit(0);
    }
    int bindStatus = bind(serverSd, (struct sockaddr*) &servAddr,
        sizeof(servAddr));
    if(bindStatus < 0)
    {
        cerr << "Error binding socket to local address" << endl;
        exit(0);
    }
    cout << "Waiting for a client to connect..." << endl;
    listen(serverSd, 5);

    struct timeval start1, end1;
    gettimeofday(&start1, NULL);
    pthread_t thread1;
    pthread_t thread2;
    srand((unsigned)time(0));
    int create_error = pthread_create(&thread1, NULL, client_inputs, NULL);
    if(!create_error)
    {
     	create_error = pthread_create(&thread2, NULL, run_games, NULL);
     	if(!create_error)
     	{
     		terminal_inputs();

     		pthread_join(thread2, NULL);
     	}
    	pthread_join(thread1, NULL);
    }
    gettimeofday(&end1, NULL);
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
