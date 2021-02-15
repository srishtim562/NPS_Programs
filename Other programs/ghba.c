// gethostbyaddr

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <errno.h> 
#include <netdb.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 

int main()
{
	char hname[256];
	char *IPaddr;
	struct hostent *hptr;
	struct in_addr addr;
	int hostname;

	// Retrieve local hostname (of the system)
	//hostname = gethostname(hname, sizeof(hname));

	// Retrieve host information
	if ((hptr = gethostbyname("www.google.com")) == NULL)
	{
		printf("Error\n");
		exit(0);
	}

	//To convert an internet network address into ASCII string
	IPaddr = inet_ntoa(*((struct in_addr *)hptr->h_addr_list[0]));

	// Contents of hostent structure
	printf("Host IP: %s\n", IPaddr);
	printf("Host name: %s\n", hptr->h_name);
	printf("Hostname aliases: %s\n", hptr->h_aliases[0]);
	
	// printf("Hostname aliases 1: %s\n", hptr->h_aliases[1]);
	// printf("Hostname aliases 2: %s\n", hptr->h_aliases[2]);
	
	printf("Address type: %d\n", hptr->h_addrtype);	// 2 = AF_INET
	printf("Address length: %d\n", hptr->h_length);

	inet_aton("172.217.163.36", &addr);
	hptr = gethostbyaddr(&addr, sizeof(addr), AF_INET);
	if (hptr != NULL && hptr->h_name != NULL)
	{
		printf("Host name: %s\n", hptr->h_name);
	}

	return 0;
}
	