#include "unp.h"

int main(int argc, char *argv[])
{
	int sockfd, listenfd, connfd;
	fd_set rset;
	int maxfd, maxi, n, i, nready;
	struct sockaddr_in servaddr, cliaddr;
	char buf[MAXLINE];
	socklen_t clilen;
	int client[FD_SETSIZE];

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port   = htons(SERV_PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	Bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

	Listen(listenfd, LISTENQ);

	maxfd = listenfd;
	maxi  = -1;
	for(i = 0; i < FD_SETSIZE; i++)
		client[i] = -1;

	FD_ZERO(&rset);
	FD_SET(listenfd, &rset);
	
	for( ; ; ){
		nready = Select(maxfd + 1, &rset, NULL, NULL, NULL);

		if(FD_ISSET(listenfd, &rset)){
			clilen = sizeof(cliaddr);
			connfd = Accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);

			for(i = 0; i < FD_SETSIZE; i++)
				if(client[i] < 0){
					client[i] = connfd;
					break;
				}
			if(i == FD_SETSIZE)
				err_quit("too many clients");

			FD_SET(connfd, &rset);
		
			if(connfd > maxfd)
				maxfd = connfd;
			if(i > maxi)
				maxi = i;

			if(--nready <= 0)
				continue;
		}

		for(i = 0; i <= maxi; i++){
			if((sockfd = client[i]) < 0)
				continue;
			if(FD_ISSET(sockfd, &rset)){
				if((n = Read(sockfd, buf, MAXLINE)) == 0){
					Close(sockfd);
					FD_CLR(sockfd, &rset);
					client[i] = -1;
				}
				else
					Writen(sockfd, buf, n);

				if(--nready <= 0)
					break;
			}
		}
	}
}
