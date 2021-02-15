#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <netinet/tcp.h>

int main()
{
	int sockfd, len, t1, t2, i;
	
	// Create a socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	i = sizeof(int); // sizeof(len)
	
	// Can also try for send buffer size by using TCP_MAXSEG instead of SO_RCVBUF, and IPPROTO_TCP instead of SOL_SOCKET
	// Include <netinet/tcp.h>
	
	if (getsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &len, &i) < 0)
		printf("Error\n");
		
	printf("Receive buffer size: %d\n",len);	// In bytes
	t1 = 11000;		// Bytes
	t2 = sizeof(int);
	
	if (setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &t1, t2) < 0)
		printf("Error\n");
		
	i = sizeof(int);
	
	// Use IPPROTO_IP, IP_TTL for hop count 
	
	if (getsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &len, &i) < 0)
		printf("Error\n");
		
	// It gets set to the given value * 2 by default (to make it large enough to store some book keeping options)
	printf("Modified receive buffer size %d\n",len);
	
	i = sizeof(len);
	if (getsockopt(sockfd, IPPROTO_IP, IP_TTL, &len, &i) < 0)
		printf("Error\n");
	printf("IP TTL: %d\n",len);
	
	i = sizeof(len);
	if (getsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &len, &i)<0)
		printf("Error\n");
	printf("Send buffer size: %d\n", len);
	
	i = sizeof(len);
	if (getsockopt(sockfd, IPPROTO_TCP, TCP_MAXSEG, &len, &i)<0)
		printf("Error\n");
	printf("TCP MAX SEG SIZE size: %d\n", len);	
	
	return 0;
}