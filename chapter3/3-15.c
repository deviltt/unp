#include "unp.h"

ssize_t readn(int fd, void *vptr, size_t n)
{
	size_t  nleft;	//remaining words
	ssize_t nread;  //the number of already readed words
	char *ptr;

	ptr   = vptr;
	nleft = n;
	while(n > 0){
		if((nread = read(fd, ptr, nleft)) < 0){
			if(errno == EINTR)
				nread = 0;
			else
				return -1;
		}
		else if(nread == 0)
			break;
		nleft -= nread;
		ptr += nread;
	}
	return (n - nleft);
}
