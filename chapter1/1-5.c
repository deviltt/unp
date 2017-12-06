/* socket()...connect()...read()/write()...close(). */

#include "unp.h"

int main(int argc, char *argv[])
{
	int sockfd, n;
	char buf[MAXLINE + 1];		//TCP是一个没有记录边界的字节流协议，后面会跟随回车符'\r'和换行符'\n'
	struct sockaddr_in servaddr;

	if(argc != 2)
		err_quit("usage: ./a.out <IPaddress>");
	
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		err_sys("socket error");

	bzero(&servaddr, sizeof(servaddr));	//结构体清零
	servaddr.sin_family = AF_INET;		//地址族
	servaddr.sin_port = htons(13000);	//端口号，尽量大一点，避免重复占用
	if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)	//呈现形式到数值
		err_quit("inet_pton error for %s", argv[1]);

	if(connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0)	//只要又函数需要一个指向套接字地址结构的指针，这个指										针必须强制类型转换成 通用套接字地址结构
		err_sys("connect error");
	
	while((n = read(sockfd, buf, MAXLINE)) > 0){
		buf[n] = 0;
		if(fputs(buf, stdout) == EOF)
			err_sys("fputs error");
	}
	if(n < 0)
		err_sys("read error");
	exit(0);
}
