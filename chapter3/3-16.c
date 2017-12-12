#include "unp.h"

ssize_t writen(int fd, const void *vptr, size_t n)
{
	size_t  nleft;
	ssize_t nwriten;
	const char *ptr;

	ptr = vptr;
	nleft = n;
	while(nleft > 0){
		if((nwriten = write(fd, ptr, nleft)) <= 0){
			if(nwriten < 0 && errni == EINTR)
				nwriten = 0;
			else
				return -1;
		}
		nleft -= nwriten;
		ptr += nwriten;
	}

	return n;
}
