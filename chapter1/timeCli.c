#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAXLINE 1024

int main(int argc, char **argv)
{
		int		sockfd, n;
		char 	recvline[MAXLINE + 1];
		struct sockaddr_in servaddr;
		if(argc != 2)
				return -1;
		if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		{
				//printf("connect failed!\n");
				return  -1;
		}
		//else printf("connect success!\n");
		bzero(&servaddr, sizeof(servaddr));
		servaddr.sin_family = AF_INET;
		servaddr.sin_port   = htons(4498);
		if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
				return -1;
		if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
		{
				printf("connect failed!\n");
				return -1;
		}
		else
		{
				 printf("connect success!\n");
		}
		while((n = read(sockfd, recvline, MAXLINE)) > 0)
		{
				recvline[n] = 0;
				if(fputs(recvline, stdout) == EOF)
						return -1;
		}
		if(n < 0)
				return -1;
		exit(0);


}
