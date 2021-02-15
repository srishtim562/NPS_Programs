/* getservbyname	looks for the file /etc/services
This function returns a pointer to servent structure

struct servent
{
	char *s_name;
	char **s_aliases;
	int s_port;
	char *s_proto;
}

*/


// daytime and dns (domain) use both tcp and udp

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>

int main()
{
	struct servent *se;
	se = getservbyname("domain", "udp");
	printf("%d\n", htons(se->s_port));
	
	// When printing, we can use htons, but htons should not be used when storing in this structure
	// Returns NULL on error, do error checking
	
	se = getservbyname("ftp", "tcp");
	printf("%d\n", htons(se->s_port));
	
	se = getservbyname("http", "tcp");
	printf("%d\n", htons(se->s_port));
	
	se = getservbyname("telnet", "tcp");
	printf("%d\n", htons(se->s_port));
	
	se = getservbyname("https", "tcp");
	printf("%d\n", htons(se->s_port));
	
	se = getservbyname("daytime", "tcp");
	printf("%d\n", htons(se->s_port));
	
	// Using getservbyport() -> reverse of getservbyname()
	// The function prints the services offered at the port
	
	se = getservbyport(htons(13), NULL);
	printf("%s\n", se->s_name);
	
	se = getservbyport(htons(21), "tcp");
	printf("%s\n", se->s_name);
	
	se = getservbyport(htons(80), "tcp");
	printf("%s\n", se->s_name);
	
	se = getservbyport(htons(23), "tcp");
	printf("%s\n", se->s_name);
	
	se = getservbyport(htons(443), "tcp");
	printf("%s\n", se->s_name);
	
	se = getservbyport(htons(13), "udp");
	printf("%s\n", se->s_name);
	
	return 0;
}