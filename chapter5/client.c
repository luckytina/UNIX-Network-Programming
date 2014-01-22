//
//  client.c
//  test
//
//  Created by yehuizhang on 14-1-19.
//  Copyright (c) 2014年 yehuizhang. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#define MAXLINE 1024  

void str_cli(FILE *,int);
int main(int argc,char *argv[])
{
	struct sockaddr_in cliaddr;
	int nread,connfd;
	char recvline[MAXLINE+1];
	memset(recvline,0,sizeof(recvline));
	connfd=socket(AF_INET,SOCK_STREAM,0);
	if(connfd<=0)
	{
		printf("socket error!\r\n");
		return 0;
    }
	bzero(&cliaddr,sizeof(struct sockaddr_in));
	cliaddr.sin_family=AF_INET;
	cliaddr.sin_port=htons(9877);
	cliaddr.sin_addr.s_addr=inet_addr("10.140.48.49");
	if(connect(connfd,(struct sockaddr*)&cliaddr,sizeof(cliaddr)))
	{
		printf("connect error!\r\n");
    }
	else
	{
			printf("successful!Please enter your message:\n");
	}
	str_cli(stdin,connfd);
	exit(0);
    
}

void str_cli(FILE *fp,int connfd)
{
	int nread;
	char recvline[MAXLINE+1];
	memset(recvline,0,sizeof(recvline));
	while(fgets(recvline,sizeof(recvline),fp) != NULL)
	{
		write(connfd,recvline,strlen(recvline));
		memset(recvline,0,sizeof(recvline));
		read(connfd,recvline,sizeof(recvline));
		fputs(recvline,stdout);
	}
	
}
