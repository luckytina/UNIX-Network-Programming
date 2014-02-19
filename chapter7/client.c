#include<stdio.h> 
#include<stdlib.h> 
#include<errno.h> 
#include<string.h> 
#include<netdb.h> 
#include<sys/types.h> 
#include<netinet/in.h> 
#include<sys/socket.h> 
#include<unistd.h> 
#include<arpa/inet.h> 
#define MAXDATASIZE 100 /*每次最大数据传输量*/ 
int main() 
{ 
	int sockfd,nbytes,serv_port; 
	char buf_serv_ip[16],buf[26]; 
	struct sockaddr_in serv_addr; 
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)
	{ 
		perror("创建套接字失败!\n"); 
		exit(1); 
	} 
	//创建套接字成功后设置其可重用的属性 
	int KeepAlive=1; 
	socklen_t KPlen=sizeof(int); 
	if(setsockopt(sockfd,SOL_SOCKET,SO_KEEPALIVE,(char *)&KeepAlive,KPlen)!=0)
	{ 
		perror("设置周期测试连接是否仍存活失败!\n"); 
		exit(1); 
	} 
	printf("请输入要连接主机的IP地址：\n"); 
	scanf("%s",buf_serv_ip); 
	printf("请输入要连接主机的端口号:\n"); 
	scanf("%d",&serv_port); 
	serv_addr.sin_family=AF_INET; 
	serv_addr.sin_addr.s_addr=inet_addr(buf_serv_ip); 
	serv_addr.sin_port=htons(serv_port); 
	bzero(&(serv_addr.sin_zero),8); 
	if(connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(struct sockaddr))==-1)
	{ 
		perror("连接服务器失败!\n"); 
		exit(1); 
	} 
	printf("连接服务器成功!\n"); 
	//在此处可以先接受判断将要接受数据的长度再创建数组 
	if((nbytes=recv(sockfd,buf,26,0))==-1)
	{ 
		perror("接受数据失败!/n"); 
		exit(1); 
	} 
	buf[nbytes]='\0'; 
	printf("接受的数据为:%s/n",buf); 
	close(sockfd); 
	return 0; 
} 
