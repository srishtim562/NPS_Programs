#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>									
#include <arpa/inet.h>

int main (int argc, char* argv[])
{       
	int create_socket,addrlen;
	int bufsize = 1024, cont;
	char *buffer = malloc(bufsize);
	char fname[256];
	struct sockaddr_in address, peer_address;
	
	if ((create_socket = socket(AF_INET, SOCK_STREAM, 0)) > 0) 
		printf("The socket was created\n");
	
	address.sin_family = AF_INET;
	address.sin_port = htons(15000);
	inet_pton(AF_INET, argv[1], &address.sin_addr);
	
	if (connect(create_socket, (struct sockaddr *)&address, sizeof(address)) == 0)
		printf("The connection was accepted with the server %s...\n",argv[1]); 
	
	getpeername(create_socket, (struct sockaddr *)&address, &addrlen);
	printf("The peer's IP is %s and port is %d \n", inet_ntoa(address.sin_addr), htons(address.sin_port));
	
	while ((cont = recv(create_socket, buffer, bufsize, 0)) > 0)
	{
		write(1, buffer, cont);
	}
	
	printf("\n");
	free(buffer);
	return close(create_socket);
}