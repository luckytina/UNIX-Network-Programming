#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>

#define SERVPORT 9877
#define MAXLINE  4096

void dg_echo(int, struct sockaddr *, socklen_t);
int main(int argc, char **argv)
{
		int 		sockfd;
		struct sockaddr_in  servaddr, cliaddr;

		sockfd	=	socket(AF_INET, SOCK_DGRAM, 0);
		memset(&servaddr, 0, sizeof(servaddr));
		servaddr.sin_family = AF_INET;
		servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
		servaddr.sin_port = htons(SERVPORT);

		bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

		dg_echo(sockfd, (struct sockaddr *)&cliaddr, sizeof(cliaddr));

}

void dg_echo(int sockfd, struct sockaddr *cliaddr, socklen_t clilen)
{
		int n;
		socklen_t len;
		char msg[MAXLINE];
		for(;;)
		{
				len = clilen;
				n = recvfrom(sockfd, msg, MAXLINE, 0, cliaddr, &len);
				sendto(sockfd, msg, n, 0, cliaddr, len);
		}
}
