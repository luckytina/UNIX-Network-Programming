#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/types.h>
#define MAXLINE 1024
void str_cli(FILE *,int);
int main(int argc, char **argv)
{
		int 	i, sockfd[5];
		struct	sockaddr_in servaddr;
		if(argc != 2)
				return (-1);
		for(i = 0;i < 5;i++)
		{
				sockfd[i] = socket(AF_INET, SOCK_STREAM, 0);
				bzero(&servaddr, sizeof(servaddr));
				servaddr.sin_family = AF_INET;
				servaddr.sin_port = htons(9877);
				inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
				connect(sockfd[i], (struct sockaddr *)&servaddr, sizeof(servaddr));
		}
		str_cli(stdin, sockfd[0]);
		exit(0);
}

void str_cli(FILE *fp, int sockfd)
{
		char sendline[MAXLINE];
		memset(revline, 0, sizeof(revline));
		while(fgets(sendline, MAXLINE, fp) != NULL)
		{
				write(sockfd, sendline, strlen(sendline));
				memset(revline, 0, sizeof(revline));
				read(sockfd, revline, sizeof(revline));
				fputs(revline, stdout);

		}
}


ssize_t readline(int fd, void *vptr, size_t maxlen)
{
		ssize_t n, rc;
		char	c, *ptr;
		ptr = vptr;
		for(n = 1; n < maxlen; n++)
		{
again:
				if((rc = read(fd, &c, 1)) == 1)
				{
						*ptr++ = c;
						if(c == '\n')
								break;
				}
				else if(rc == 0)
				{
						*ptr = 0;
						return (n - 1);
				}
				else
				{
						if(errno == EINTR)
							goto again;
						return (-1);

				}
		}
		*ptr = 0;
		return (n);
}




