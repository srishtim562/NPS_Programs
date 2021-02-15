// Time server -> sends the current time to the client
// Implemented as an iterative server (it servers one client at a time)

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>                                        
#include <fcntl.h>
#include <arpa/inet.h>
#include <string.h>
#include <time.h>


int main()
{
	int listenfd, connfd, addrlen;
	char fname[256];
	time_t ticks;
	struct sockaddr_in address, cliaddr;
	
	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) > 0)
		printf("The socket is created\n");
		
	address.sin_family=AF_INET;
	address.sin_addr.s_addr=INADDR_ANY;
	address.sin_port=htons(15000);

	if (bind(listenfd, (struct sockaddr *)&address, sizeof(address)) == 0)
		printf("Binding Socket\n");
		
	listen(listenfd, 4);
	getsockname(listenfd, (struct sockaddr*)&address, &addrlen); 
	                 
	printf("The server %s is connected, binded at port no %d \n",  inet_ntoa(address.sin_addr), htons(address.sin_port));

	for (;;)    
	{
		 addrlen = sizeof(cliaddr);
		 connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &addrlen);
		 //printf("the client  %s is connected \n",  inet_ntoa(cliaddr.sin_addr));
		 getpeername(connfd, (struct sockaddr*)&cliaddr, &addrlen);                       
		 printf("The client's IP address is  %s and port number is %d \n",  inet_ntoa(cliaddr.sin_addr), htons(cliaddr.sin_port));
		 ntohs(cliaddr.sin_port);														//-> ???
		 ticks = time(&ticks);
		 snprintf(fname, sizeof(fname), "Current Time is = %s", ctime(&ticks));
		 send(connfd, fname, 37, 0);			 
		 printf("Current time = %s", ctime(&ticks));
		 close(connfd);
	}
	
	close(listenfd);
}
