#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>

int main(int argc, char **argv)
{
		char *ptr, **pptr;
		char str[16];
		struct hostent *hptr;
		printf("baidu");
		while(--argc > 0)
		{
				ptr = *++argv;
				if((hptr = gethostbyname(ptr)) == NULL)
				{
						printf("hh");
						return -1;
				}
				printf("official hostname:%s\n", hptr->h_name);
				for(pptr = hptr -> h_aliases; *pptr != NULL; pptr++)
				{
						printf("\talias: %s\n", *pptr);
				}
				switch (hptr -> h_addrtype)
				{
						case AF_INET:
								pptr = hptr -> h_addr_list;
								for(; *pptr != NULL; pptr++)
										printf("\taddress:%s\n", inet_ntop(hptr->h_addrtype, *pptr, str, sizeof(str)));
								break;
						default:
								break;
				}
		}
		return 0;
}

