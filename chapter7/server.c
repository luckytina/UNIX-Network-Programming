#include<stdio.h> 
#include<stdlib.h> 
#include<sys/socket.h> 
#include<errno.h> 
#include<string.h> 
#include<sys/types.h> 
#include<netinet/in.h> 
#include<sys/wait.h> 
#include<arpa/inet.h> 
#include<unistd.h> 

#define SERVPORT 6000 //设定服务器服务端口为6000 
#define MAX_LISTEN_SOCK_NUM 20 //设定可监听套接字的最大个数为20 
int main() 
{ 
	//sockfd为本地监听套接字标识符，client_fd为客户端套接字标识符 
	int sockfd,client_fd; 
	struct sockaddr_in my_addr; 
	struct sockaddr_in client_addr; 

	//创建本地监听套接字 
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)
	{ 
		perror("套接字创建失败!/n"); 
		exit(1); 
	} 

	//设置套接字的属性使它能够在计算机重启的时候可以再次使用套接字的端口和IP 
	int err,sock_reuse=1; 
	err=setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,(char *)&sock_reuse,sizeof(sock_reuse)); 
	if(err!=0)
	{ 
		printf("套接字可重用设置失败!/n"); 
		exit(1); 
	} 
	my_addr.sin_family=AF_INET; 
	my_addr.sin_port=htons(SERVPORT); 
	my_addr.sin_addr.s_addr=INADDR_ANY; 
	bzero(&(my_addr.sin_zero),8); 
	//绑定套接字 
	if(bind(sockfd,(struct sockaddr *)&my_addr,sizeof(struct sockaddr))==-1)
	{ 
		perror("绑定失败!/n"); 
		exit(1); 
	} 
	//设置监听 
	if((listen(sockfd,MAX_LISTEN_SOCK_NUM))==-1)
	{ 
		perror("设置监听失败!/n"); 
		exit(1); 
	} 
	printf("套接字进入监听状态，等待请求连接：/n"); 

	while(1)
	{ 

		//有连接请求时进行连接 
		socklen_t sin_size=sizeof(struct sockaddr_in); 
		if((client_fd=accept(sockfd,(struct sockaddr *)&client_addr,&sin_size))==-1)
		{ 
			perror("接受连接失败!/n"); 
			continue; 
		} 

		int opt; 
		socklen_t len=sizeof(int); 
		if((getsockopt(sockfd,SOL_SOCKET,SO_KEEPALIVE,(char*)&opt,&len))==0)
		{ 
			printf("SO_KEEPALIVE Value: %d/n", opt); 
		} 
		printf("接到一个来自%s的连接/n",inet_ntoa(client_addr.sin_addr)); 
		//创建子进程来处理已连接的客户端套接字 

		if(send(client_fd,"您好，您已经连接成功!/n",50,0)==-1)
		{ 
			perror("发送通知信息失败!/n"); 
			exit(0); 
		} 

	} 
	close(client_fd); 

	return 0; 
} 
