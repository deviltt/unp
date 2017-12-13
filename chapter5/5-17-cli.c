#include "unp.h"

void str_cli(FILE *fp, int sockfd)
{
	char sendbuf[MAXLINE], recbuf[MAXLINE];

	while(Fgets(sendbuf, MAXLINE, fp) != NULL){
		Writen(sockfd, sendbuf, strlen(sendbuf));
		
		if(Readline(sockfd, recbuf, MAXLINE) == 0)
			err_quit("readline error");

		Fputs(recbuf, stdout);  
	}
}

int main(int argc, char *argv[])
{
	int listenfd;
	struct sockaddr_in servaddr;

	if(argc != 2)
		err_quit("usage: ./a.out IPaddress\n");

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port   = htons(SERV_PORT);
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	Connect(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

	str_cli(stdin, listenfd);

	exit(0);	
}
