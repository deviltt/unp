/* socket()...bind()...listen()...accept()...read()/write()...close(). */
#include "unp.h"
#include <time.h>

int main(int argc, char *argv[])
{
	int listenfd, connfd;
	struct sockaddr_in servaddr;
	char buf[MAXLINE];
	time_t ticks;

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port   = htons(13000);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);	//这样设置，服务器可以在任意网络接口上接受客户连接
	
	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

	Listen(listenfd, LISTENQ);
	
	for( ; ; ){
		connfd = Accept(listenfd, (SA *) NULL, NULL);
		ticks = time(NULL);
		snprintf(buf, sizeof(buf), "%.24s\r\n", ctime(&ticks));
		Write(connfd, buf, strlen(buf));
		Close(connfd);
	}
}
