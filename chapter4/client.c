#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#define MAXLINE 4096
#define LISTENQ 1024

int main(int argc, char **argv)
{
    int sockfd, n;
    char recvline[MAXLINE + 1];
    struct sockaddr_in servaddr;
    /*if (argc != 2) {
    
    }*/
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(13);
	printf("1");
    inet_pton(AF_INET, "10.140.48.49", &servaddr.sin_addr);
	printf("2");
    connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    
    while ((n = read(sockfd, recvline, MAXLINE)) > 0) {
        recvline[n] = 0;
        fputs(recvline, stdout);
    }
    return 0;
}

