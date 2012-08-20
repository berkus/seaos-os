#include "ksyscall.h"
#include <sys/types.h>
#include <sys/statfs.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
int makedev(int maj, int min)
{
	#define GETDEV(maj, min) (maj*256+min)
	return GETDEV(maj, min);
}


int
mkfifo (path, mode)
     const char *path;
     mode_t mode;
{

  return (mknod (path, ((mode&0xFFF) | S_IFIFO), 0));

}

int mknod(const char *path, mode_t m, dev_t d)
{
	int ret= syscall(105, (int)path, m, d, 0, 0);
	if(ret < 0)
	{
		errno = -ret;
		return -1;
	}
	return ret;
}

int sys_pipe(int *f)
{
	int ret = syscall(83, (int)f, 0, 0, 0, 0);
	if(ret < 0)
	{
		errno = -ret;
		return -1;
	}
	return ret;
}

int pipe(int *f)
{
	return sys_pipe(f);
}
