#include<stdio.h>
#include<netdb.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#define MAX 80 
#define PORT 8081 
#define SA struct sockaddr 


void func(int sockfd) 
{ 
    char buff[MAX]; 
    int n; 
    
for (;;) 
{ 
    // bzero(Points to a buffer that zeros are copied into,
           //Is the number of zeros to be copied into the buffer)
	bzero(buff, MAX);
	
	// read(file descripter,buffer to read data from,length of buffer))
	read(sockfd, buff, sizeof(buff));
	
	printf("From client: %s\t To client : ", buff);
	 
	bzero(buff, MAX);
	 
  	n = 0; 
 	while ((buff[n++] = getchar()) != '\n');
 	 
	write(sockfd, buff, sizeof(buff)); 
	
	// Check if the message is "exit"
 	if (strncmp("exit", buff, 4) == 0) 
 	{ 
		printf("Server Exit...\n"); 
            break; 
    } 
} 

} 


int main() 
{ 
    int sockfd, connfd, len; 
    struct sockaddr_in servaddr, cli;
    
    // Create the Socket 
    // sockid = socket(family,type, protocol)
    // family: IPV4 Internet protocols
    // Sock_Stream: reliable, 2 Way, connection-basic service
    // IPPROTO_TCP, IPPROTO_UDP, usually set to 0 default
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	
    if (sockfd == -1) 
    { 
		printf("socket creation failed...\n"); 
		exit(0); 
    } 
    else
		printf("Socket successfully created..\n"); 

	bzero(&servaddr, sizeof(servaddr));
	
	// Internet Protocol 
	servaddr.sin_family = AF_INET;
	// Address Port 
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	// Internet Address 
	servaddr.sin_port = htons(PORT); 
	
	
	// status = bind(sockid,&addrport, size)
	
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) 
    { 
		printf("socket bind failed...\n"); 
		exit(0); 
    } 
    else
		printf("Socket successfully binded..\n");
	
	// status = listen(sockid, queuelimit)
    if ((listen(sockfd, 5)) != 0) 
    { 
		printf("Listen failed...\n"); 
		exit(0); 
    } 
    else            	
    	printf("Server listening..\n"); 

	len = sizeof(cli);
	
	// s = accept(sockid, &clientaddr, $addrlen)
	connfd = accept(sockfd, (SA*)&cli, &len); 
	
    if (connfd< 0) 
    { 
		printf("server acccept failed...\n"); 
		exit(0); 
    } 
    else
		printf("server acccept the client...\n"); 

	func(connfd); 

    close(sockfd); 
    
}

