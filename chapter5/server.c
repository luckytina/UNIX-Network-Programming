//
//  server.c
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
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define MAXLINE 1024
void str_echo(int);
int main(int argc,char *argv[])
{
	struct sockaddr_in serveraddr,cliaddr;
	char recvline[MAXLINE+1];
	int nread;
	int listenfd,connfd,connlen;
	int pid_t;
	connlen=1;
	memset(&cliaddr,0,sizeof(cliaddr));
	bzero(&serveraddr,sizeof(struct sockaddr_in));
	serveraddr.sin_port=htons(9877);
	serveraddr.sin_family=AF_INET;
	if(argc>=2){
		if(!inet_aton(argv[1],&serveraddr.sin_addr))
			printf("inet_aton error!\r\n");
        return -1;
        
	}
	serveraddr.sin_addr.s_addr=htonl(INADDR_ANY);
	if((listenfd=socket(AF_INET,SOCK_STREAM,0))<=0)
	{
		printf("socket error!\r\n");
		return 0;
    }
	bind(listenfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
	listen(listenfd,5);
	for(;;)
	{
		connfd=accept(listenfd,(struct sockaddr*)&cliaddr,&connlen);
		if((pid_t=fork())==0)
        {
            close(listenfd);
            str_echo(connfd);
			close(connfd);
            exit(0);
        }
		close(connfd);
    }
	return 0;
}

void str_echo(int connfd)
{
	char recvline[MAXLINE+1];
	int nread;
	memset(recvline,0,sizeof(recvline));

	while((nread=read(connfd,recvline,sizeof(recvline)))> 0 )
	{
		fputs(recvline,stdout);
		if(nread<=0)
		{
			printf("read error!\r\n");
			exit(0);
    	}
		nread=write(connfd,recvline,strlen(recvline));
		if(nread<=0)
		{
			printf("write error!\r\n");
			exit(0);
    	}
	}
}

