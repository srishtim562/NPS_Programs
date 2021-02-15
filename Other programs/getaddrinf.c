/*The addrinfo structure used by getaddrinfo() contains the following
       fields:

           struct addrinfo {
               int              ai_flags;
               int              ai_family;
               int              ai_socktype;
               int              ai_protocol;
               socklen_t        ai_addrlen;
               struct sockaddr *ai_addr;
               char            *ai_canonname;
               struct addrinfo *ai_next;
           };

       The hints argument points to an addrinfo structure that specifies
       criteria for selecting the socket address structures returned in the
       list pointed to by res.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

int main()
{
	struct addrinfo hints, *res;
	// Get result back in res, can have both IPv4 and IPv6
	int errcode;
	char addrstr[100];
	void *ptr;
	
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;		
	// if AF_UNSPEC, it gives both IPv4 and IPv6 addresses
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags |= AI_CANONNAME;	// Only the first one is specified as canonnical name, others are specified as null
	
	errcode = getaddrinfo("www.google.com", NULL, &hints, &res);
	
	if (errcode != 0)
	{
		//perror("getaddrinfo");
		//return -1
		
		gai_strerror(errcode);
		printf("Error code: %d\n", errcode);
	}
	
	printf("Host: %s\n", "www.google.com");
	while (res)
	{
		inet_ntop(res->ai_family, res->ai_addr->sa_data, addrstr, 100);
		
		switch (res->ai_family)
		{
			case AF_INET:
				ptr = &((struct sockaddr_in *) res->ai_addr)->sin_addr;
				break;
				
			case AF_INET6:
				ptr = &((struct sockaddr_in6 *) res->ai_addr)->sin6_addr;
				break;
				
		}
		
		inet_ntop(res->ai_family, ptr, addrstr, 100);
		// family, structure, 100 = size of address structure
		printf("IPv%d address: %s (%s)\n", res->ai_family == AF_INET6 ? 6 : 4, addrstr, res->ai_canonname);
		res = res->ai_next;
	}
	
	freeaddrinfo(res);
	
	return 0;
}