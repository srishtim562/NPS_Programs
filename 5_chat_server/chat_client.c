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

void str_cli(int sockfd)
{

	char buff[256];
	char message[256];

	while(1)
	{
		printf("To server: ");
		memset(message, 0, sizeof(message));
		fgets(message, sizeof(message), stdin);
		send(sockfd, message, sizeof(message), 0);	
		
		memset(buff, 0, sizeof(buff));
		recv(sockfd, &buff, sizeof(buff), 0); 
		printf("From server: %s\n", buff);	

		
	}

}


int main(int argc, char *argv[])
{
	int create_socket;
	struct sockaddr_in address;

	if ((create_socket = socket(AF_INET, SOCK_STREAM, 0)) > 0)
		printf("The socket was created\n");
	
	address.sin_family = AF_INET;
	address.sin_port = htons(15001);	//Can use port no. directly, no need of htons, since it's on the local system, same port no. in both server and client programs
	inet_pton(AF_INET, argv[1], &address.sin_addr);		//argv[1] -> Server's IP address (loopback address = 127.0.0.1) passed as a command line argument
	
	if (connect(create_socket, (struct sockaddr *)&address, sizeof(address)) == 0)
		printf("The connection was accepted with the server %s\n",argv[1]);
	else
		printf("Error in connect\n");		//eg. starting the client without starting the server, using a different port no. than on the port the server is running on (eg. 15002)
	
	str_cli(create_socket);				//For accepting data from the user and printing it back

	return close(create_socket);
}