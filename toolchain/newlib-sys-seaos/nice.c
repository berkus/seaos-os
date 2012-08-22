#include "ksyscall.h"
#include <signal.h>
#include <stdio.h>

int nice(int inc)
{
	/* which, who, value, flags */
	int ret = syscall(64, 0, 0, inc, 0, 0);
	if(ret < 0)
	{
		errno = -ret;
		return -1;
	}
	return ret;
}

int setpriority(int which, unsigned who, int value)
{
	/* which, who, value, flags */
	int ret = syscall(64, which, (int)who, value, 1, 0);
	if(ret < 0)
	{
		errno = -ret;
		return -1;
	}
	return ret;
}

int getpriority(int which, int id)
{
	int ret = syscall(115, which, id, 0, 0, 0);
	if(ret < 0)
	{
		errno = -ret;
		return -1;
	}
	return 0;
}
