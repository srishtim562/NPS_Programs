#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <arpa/inet.h>

		
void str_echo(int connfd)						//Reads from and writes to the client
{	
	int l;
	char fname[256];
	char buff[11];

	while (recv(connfd, fname, sizeof(fname), 0) > 0)		//recv -> for TCP, recvfrom, sendto -> for UDP, recv returns the number of successfully read characters to n
	{
		memset(buff, 0, sizeof(buff));
		FILE *fp = fopen(fname, "r");
		if (fp == NULL)
		{
			printf("ERROR\n");
			perror("fopen");
			strcpy(buff, "ERROR\n");
			send(connfd, buff, sizeof(buff), 0);
			goto send_EOF;
		}
	
		while (fread(buff, 1, 1, fp) > 0)
		{
			send(connfd, buff, sizeof(buff), 0);	
		}
		fclose(fp);
send_EOF:
		strcpy(buff, "EOF");
		send(connfd, buff, sizeof(buff), 0);
	}

}


int main()
{
	int listenfd, connfd, addrlen, pid;
	struct sockaddr_in address;		// To store the server's details
	
	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) > 0)		// AF_INET = IPv4, SOCK_STREAM, 0 = kernel chooses the protocol
		printf("The socket was created\n");
	
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;		//Wildcard IP address
	address.sin_port = htons(15001);

	if (bind(listenfd, (struct sockaddr *)&address, sizeof(address)) == 0)
		printf("Binding Socket\n");

	listen(listenfd, 3);		//sockfd, backlog = 3 => server can handle 3 clients
	printf("Server is listening\n");

	for (;;)				//Want server to keep running till EOF from the client is received
	{
		addrlen = sizeof(struct sockaddr_in);	
		connfd = accept(listenfd, (struct sockaddr *)&address, &addrlen);
		
		if (connfd > 0)
			printf("The client %s is connected...\n", inet_ntoa(address.sin_addr));		//ntoa = network to ASCII
		
		if ((pid = fork()) == 0)
		{
			printf("Inside child\n");
			close(listenfd);		//Close the listenfd in the child (refer slide 12 of concurrent servers PPT), the child doesn't listen, it just connects with the client
			str_echo(connfd);		//Read and write between client and child happen over connfd
			exit(0);
		}

	
		close(connfd);			//Close connfd in the parent, parent keeps listening, it doesn't connect to the client, it forks a child to connect to the client
	}

	return 0;	
}