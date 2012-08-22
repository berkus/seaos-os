#include <sys/times.h>
#include <sys/time.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <unistd.h>
#include <limits.h>
#include <sys/stat.h>
#include "linux_fsinfo.h"
#include "ksyscall.h"
#include <stdio.h>
#include "sys/dirent.h"
#include <netdb.h>
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
	return (void *)ret;
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

int posix_memalign (void **memptr, size_t alignment, size_t size)
{
	void *mem;
	
	/* Test whether the ALIGNMENT argument is valid.  It must be a power
	 of two mult*iple of sizeof (void *).  */
	//printf("Mem %d %d...", alignment, size);fflush(0);
	if (alignment % sizeof (void *) != 0 || (alignment & (alignment - 1)) != 0) {
		//printf("OUT\n");fflush(0);
		return EINVAL;
	}
	
	mem = (void *)memalign (alignment, size);
	//printf("%x\n", mem);fflush(0);
	if (mem != NULL)
	{
		*memptr = mem;
		return 0;
	}
	
	return ENOMEM;
}
int getpagesize()
{
	return sysconf(_SC_PAGESIZE);
}


