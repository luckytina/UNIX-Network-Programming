#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define MAXLINE 1024
#define LISTENQ 1024
int main(int argc, char **argv)
{
		int listenfd, connfd;
		struct sockaddr_in servaddr;
		pid_t pid;
		char buff[MAXLINE];
		time_t ticks;
		if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) <0 )
				return -1;
		bzero(&servaddr, sizeof(servaddr));
		servaddr.sin_family = AF_INET;
		servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
		servaddr.sin_port = htons(4498);
		bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
		listen(listenfd, LISTENQ);
		for(;;)
		{
				connfd = accept(listenfd, (struct sockaddr *)NULL, NULL);
				if((pid = fork()) > 0)
				{
					close(listenfd);
					ticks = time(NULL);

					snprintf(buff, sizeof(buff), "%.24s\r\n",ctime(&ticks));

					write(connfd, buff, strlen(buff));
					exit(0);
				}

				close(connfd);
		}
		
}
