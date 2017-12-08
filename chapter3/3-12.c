#include "unp.h"

int inet_pton(int family, const char *strptr, void *addrptr)	//presentation to numeric
{
	if(family == AF_INET){
		struct in_addr in_val;
	
		if(inet_aton(strptr, &in_val)){
			memcpy(addr, &in_val, sizeof(struct in_addr));	//memcpy(*dst, *src, size);
			return 1;
		}
		return 0;
	}
	errno = EAFNOSUPPORT;
	return -1;
}
