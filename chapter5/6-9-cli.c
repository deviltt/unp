#include "unp.h"

#define oops(s) {perror(s); exit(1);}

void str_cli(FILE *fd, int sockfd)
{
	char sendbuf[MAXLINE], recbuf[MAXLINE];
	fd_set reset;
	int maxfd;

	FD_ZERO(&reset);

	for( ; ; ){
		FD_SET(fileno(fd), &reset);
		FD_SET(sockfd    , &reset);
		maxfd = max(fileno(fd), sockfd) + 1;
		Select(maxfd, &reset, NULL, NULL, NULL);

		if(FD_ISSET(sockfd, &reset)){
			if(Readline(sockfd, recbuf, MAXLINE) == 0)
				err_quit("str_cli:server terminated prematurely");
			Fputs(recbuf, stdout);
		}

		if(FD_ISSET(fileno(fd), &reset)){
			if(Fgets(sendbuf, MAXLINE, stdin) == NULL)
				return;
			Writen(sockfd, sendbuf, strlen(sendbuf));
		}
	}
}

int main(int argc, char *argv[])
{
	int sockfd;
	struct sockaddr_in servaddr;


	if(argc != 2)
		oops("usage: ./a.out IPaddress");
	sockfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_port   = htons(SERV_PORT);
	servaddr.sin_family = AF_INET;
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	Connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

	str_cli(stdin, sockfd);
	
	exit(0);
}
