#include "unp.h"

ssize_t(int fd, void *vptr, size_t maxlen)
{
	ssize_t n,rc;
	char c, *ptr;

	ptr = vptr;

	for(n = 1; n < maxlen; n++){
	again:
		if((rc =  read(fd, &c ,1)) == 1){	//read one char and store in &c
			*ptr++ = c;
			if(c == '\n')
				break;
		}
		else if(rc == 0){
			*ptr = 0;
			return (n - 1);
		}
		else{
			if(errno == EINTR)
				goto again;
			return -1;
		}
	}
	*ptr = 0;
	return n;
}
