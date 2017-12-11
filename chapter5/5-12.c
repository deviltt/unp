#include "unp.h"

void str_echo(int sockfd)
{
	ssize_t n;
	char buf[MAXLINE];

again:
	while((n = read(sockfd, buf, MAXLINE)) > 0)
		Writen(sockfd, buf, n);
	
	if(n < 0 && errno == EINTR)
		goto again;
	else if(n < 0)
		err_sys("str_echo: read error");
}

void sig_chld(int signum)
{
	pid_t pid;
	int stat;
	while((pid = waitpid(-1, &stat, WNOHANG)) > 0)
		printf("child %d terminated\n", pid);
	return 0;
}

int main()
{
	int listenfd, connfd;
	pid_t child_pid;
	socklen_t clilen;
	struct sockaddr_in cliaddr, servaddr;
	
	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);	//SERV_PORT is the port that we all known, its number is 9877
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	Bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

	Listen(listenfd, LISTENQ);

	Signal(SIGCHLD, sig_chld);

	for( ; ; ){
		clilen = sizeof(cliaddr);
		if((connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen)) < 0){
			if(errno == EINTR)
				continue;
			else
				err_sys("accept error");
		}
		if((child_pid = Fork()) == 0){
			Close(listenfd);
			str_echo(connfd);
			exit(0);
		}
		Close(connfd);
	}
	//exit(0);
}
