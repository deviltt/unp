#include "unp.h"

#define oops(s) {perror(s); exit(1);}

void str_echo(int sockfd)
{
	int n;
	char line[MAXLINE];
	long arg1, arg2;	

	for( ; ; ){
		if((n = read(sockfd, line, MAXLINE)) == 0)
			return;		
		if(sscanf(line, "%ld%ld", &arg1, &arg2) == 2)
			snprintf(line, sizeof(line), "%ld\n", arg1 + arg2);
		else
			snprintf(line, sizeof(line), "input error\n");
	
		n = strlen(line);
		Writen(sockfd, line, n);
	}
}

void sig_chld(int sig_num)
{
	pid_t pid;
	int stat;

	if((pid = waitpid(-1, &stat, WNOHANG)) > 0)
		printf("child %d terminated\n", pid);

	return;
}

int main()
{
	int listenfd, connfd;
	struct sockaddr_in cliaddr, servaddr;	
	socklen_t clilen;
	pid_t child_pid;

//	listenfd = Socket(AF_INET, SOCK_STREAM, 0);
	if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == EOF)
		oops("socket error");

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port   = htons(SERV_PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == EOF)
		oops("bind error");

	Listen(listenfd, LISTENQ);

	signal(SIGCHLD, sig_chld);

	for( ; ; ){
		clilen = sizeof(cliaddr);
		if((connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen)) == EOF){
			if(errno == EINTR)
				continue;
			else
				err_sys("accept error");
		}
		if((child_pid = fork()) < 0){
			oops("fork error");
		}
		else if(child_pid == 0){
			Close(listenfd);
			str_echo(connfd);
			exit(0);
		}
		Close(connfd);
	}
}
