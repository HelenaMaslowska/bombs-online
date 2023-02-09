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
using namespace std;
//Server side
/*

g++ server.cpp -o server
./server 8080

*/

struct Client{
	int sd=0;
	string nickname;
	int room;
};

struct Room{
	vector<Client> clients;
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
    int bytesRead, bytesWritten = 0;
    fd_set readfds;
    int max_sd;
    vector<Client> clients;
    int clients_size=0;
    while(1)
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
        
        int activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);  
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
                     
                //Echo back the message that came in 
                else 
                {  
                    //set the string terminating NULL byte on the end 
                    //of the data read   
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
    //we need to close the socket descriptors after we're all done
    gettimeofday(&end1, NULL);
    //close(newSd);
    for(int i=0;i<clients_size;i++){
    	close(clients[i].sd);
    }
    close(serverSd);
    cout << "********Session********" << endl;
    cout << "Bytes written: " << bytesWritten << " Bytes read: " << bytesRead << endl;
    cout << "Elapsed time: " << (end1.tv_sec - start1.tv_sec) 
        << " secs" << endl;
    cout << "Connection closed..." << endl;
    return 0;   
}
