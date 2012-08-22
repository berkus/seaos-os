#include "ksyscall.h"
#include <signal.h>
#include <stdio.h>

int waitpid(int pid, int *stat, int opt)
{
	int ret = syscall(104, pid, (int)stat, opt, 0, 0);
	if(ret < 0) {
		errno = -ret;
		return -1;
	}
	return ret;
}

int wait(int *stat)
{
	int ret = syscall(104, -1, (int)stat, 0, 0, 0);
	if(ret < 0) {
		errno = -ret;
		return -1;
	}
	return ret;
}

int waitagain()
{
	return syscall(127, 0, 0, 0, 0, 0);
}

int sbrk (int nbytes)
{
	int ret = syscall(SYS_sbrk, nbytes, 0, 0, 0, 0);
	if(ret < 0) {
		errno = -ret;
		return -1;
	}
	return ret;
}

unsigned alarm(unsigned s)
{
	int ret = syscall(55, s, 0, 0, 0, 0);
	if(ret < 0)
	{
		errno = -ret;
		return -1;
	}
	return ret;
}

mode_t umask(mode_t mode)
{
	int ret = syscall(108, mode, 0, 0, 0, 0);
	if(ret < 0) {
		errno = -ret;
		return -1;
	}
	return ret;
}
