#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAXLINE 1024
void str_cli(FILE *, int);
int main(int argc, char **argv)
{
		int 	sockfd;
		struct  sockaddr_in servaddr;
		
		bzero(&servaddr, sizeof(servaddr));
		servaddr.sin_family = AF_INET;
		servaddr.sin_port   = htons(9877);

		if(argc < 2) exit(1);
		if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr) < 1)
			   	exit(1);
		if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
				exit(1);

		if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
				exit(1);

		str_cli(stdin, sockfd);

		exit(0);
}


void str_cli(FILE *fp, int sockfd)
{
		char sendline[MAXLINE], recline[MAXLINE];
		memset(sendline, 0, sizeof(sendline));
		while(fgets(sendline, MAXLINE, fp) != NULL)
		{
				write(sockfd, sendline, MAXLINE);
				sleep(1000);
				memset(recline, 0, sizeof(recline));
				read(sockfd, recline, MAXLINE);
				fputs(recline, stdout);
		}
}
