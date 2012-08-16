#include <stdio.h>
#include <stdlib.h>
#include "ksyscall.h"
#include <sys/types.h>
void *__mmap(void *addr, size_t len, int prot, int flags, int fildes, off_t off)
{
	struct mmapblock {
		size_t len;
		off_t off;
	} c;
	c.len = len;
	c.off = off;
	unsigned ret = syscall(50, (unsigned)addr, (unsigned)&c, prot, flags, fildes);
	if(ret < 0x1000) {
		/* Is an error code */
		errno = ret;
		return (void *)-1;
	}
	return ret;
}

int __munmap(void *addr, size_t sz)
{
	int ret = syscall(51, (unsigned)addr, sz, 0, 0, 0);
	if(ret < 0)
	{
		errno = -ret;
		return -1;
	}
	return 0;
}
