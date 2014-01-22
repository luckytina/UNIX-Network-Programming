#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>

#define MAXLINE 1024
#define LISTENQ 1024
void str_echo(int);
int main()
{
	int		listenfd, connfd;
	struct	sockaddr_in serv;
	pid_t pid;

	serv.sin_family      = AF_INET;
	serv.sin_addr.s_addr = htonl(INADDR_ANY);
	serv.sin_port		 = htons(9877);

	if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
			exit(1);
	if(bind(listenfd, (struct sockaddr *)&serv, sizeof(serv)) < 0)
			exit(1);
	if(listen(listenfd, LISTENQ) < 0)
			exit(1);
	for(;;)
	{
			connfd = accept(listenfd, (struct sockaddr *)NULL, NULL);
			if((pid = fork()) != 0)
			{
					close(listenfd);
					str_echo(connfd);
					exit(0);
			}
			close(connfd);
	}

}

void str_echo(int sockfd)
{
		ssize_t  n;
		char 	 recline[MAXLINE];
		while((n = read(sockfd, recline, sizeof(recline))) > 0)
		{
				write(sockfd, recline, sizeof(recline));
				fputs(recline, stdout);
		}
}
