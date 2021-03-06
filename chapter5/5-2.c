#include <unp.h>

void str_echo( int sockfd)
{
	ssize_t n;
	char buf[MAXLINE];

again:
	while((n = read(sockfd, buf, MAXLINE)) > 0)
		Write(sockfd, buf, n);

	if(n < 0 && errno == EINTR)
		goto again;
	else if(n < 0)
		err_sys("str_echo: read error");
}

void sig_chld(int signum)
{
	pid_t pid;
	int stat;
	
	pid = wait(&stat);
	printf("child %d terminated\n", pid);
	return;
}

int main()
{
	int listenfd, connfd;
	struct sockaddr_in cliaddr, servaddr;
	pid_t childpid;
	socklen_t clilen;

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);

	Bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

	Listen(listenfd, LISTENQ);

  	Signal(SIGCHLD, sig_chld);

	for( ; ; ){
		clilen = sizeof(cliaddr);
		connfd = Accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);
		if((childpid = Fork()) == 0){
			Close(listenfd);
			str_echo(connfd);	
			exit(0);
		}
		Close(connfd);
	}
}
