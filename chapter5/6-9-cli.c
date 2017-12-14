#include "unp.h"

#define oops(s) {perror(s); exit(1);}
/*
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
*/

void str_cli(FILE *fp, int sockfd)
{
	int maxfdp, stdineof;
	char buf[MAXLINE];
	fd_set reset;
	int n;

	stdineof = 0;
	FD_ZERO(&reset);
	for( ; ; ){
		if(stdineof == 0)
			FD_SET(fileno(fp), &reset);
		FD_SET(sockfd, &reset);
		maxfdp = max(fileno(fp), sockfd) + 1;
		Select(maxfdp, &reset, NULL, NULL, NULL);

		if(FD_ISSET(sockfd, &reset)){
			if((n = Read(sockfd, buf, MAXLINE)) == 0){
				if(stdineof == 1)
					return;
				else
					err_quit("error serv close");	//when the server is closed, this will print;
			}
			Write(fileno(stdout), buf, n);
		}
		if(FD_ISSET(fileno(fp), &reset)){		//when the server is closed, this will not act, stdineof = 0;
			if((n = Read(fileno(fp), buf, MAXLINE)) == 0){
				stdineof = 1;
				Shutdown(sockfd, SHUT_WR);
				FD_CLR(fileno(fp), &reset);
				continue;
			}
			Write(sockfd, buf, n);
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
