#include "ksyscall.h"
#include <sys/types.h>
#include <sys/statfs.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
int fsync(int f)
{
	int ret = syscall(54, f, 0, 0, 0, 0);
	if(ret < 0)
	{
		errno = -ret;
		return -1;
	}
	return ret;
}

void sync()
{
	syscall(52, 0, 0, 0, 0, 0);
}

int fdatasync(int file)
{
	return fsync(file);
}

int fclean(FILE *f)
{
	return fflush(f);
}
