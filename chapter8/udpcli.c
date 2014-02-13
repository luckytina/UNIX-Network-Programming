#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#define SERV_PORT 9877
#define MAXLINE 4096
void dg_cli(FILE *, int, const struct sockaddr *, int);
int main(int argc, char **argv)
{
		int sockfd;
		//套接字地址结构
		struct sockaddr_in servaddr;
		if(argc != 2)
				exit(0);
		//套接字
		sockfd = socket(AF_INET, SOCK_DGRAM, 0);
		bzero(&servaddr, sizeof(servaddr));

		//套接字地址结构初始化
		servaddr.sin_family = AF_INET;
		servaddr.sin_port	= htons(SERV_PORT);
		inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
		dg_cli(stdin, sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr));
		exit(0);
}

void dg_cli(FILE *fp, int sockfd, const struct sockaddr *servaddr, int servlen)
{
		int n;
		char sendline[MAXLINE], recvline[MAXLINE + 1];
		while(fgets(sendline, MAXLINE, fp) != NULL)
		{
				sendto(sockfd, sendline, strlen(sendline), 0, servaddr, servlen);
				n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);
				recvline[n] = 0;
				fputs(recvline, stdout);
		}
}

