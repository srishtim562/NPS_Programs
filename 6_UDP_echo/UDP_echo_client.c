#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>


void str_cli(FILE *fp, int sockfd, struct sockaddr *serv_address, int servlen)
{	
	int bufsize = 1024;
	char *buffer = malloc(bufsize);
	
	while (fgets(buffer, bufsize, fp) != NULL)
	{
		sendto(sockfd, buffer, sizeof(buffer), 0, serv_address, servlen);
		if (recvfrom(sockfd, buffer, bufsize, 0, NULL, NULL) > 0)
			fputs(buffer, stdout);
	}
	
	printf("\nEOF\n");
	free(buffer);
}


int main (int argc, char *argv[])
{
	int sockfd;
	struct sockaddr_in serv_address;
	
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) > 0)
		printf("The socket was created\n");
		
	serv_address.sin_family = AF_INET;
	serv_address.sin_port = htons(16001);
	inet_pton(AF_INET, argv[1], &serv_address.sin_addr);
	
	str_cli(stdin, sockfd, (struct sockaddr *)&serv_address, sizeof(serv_address));
	return close(sockfd);
}