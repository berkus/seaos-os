#include "ksyscall.h"
#include <sys/types.h>
#include <sys/statfs.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

/* [f]chdir - change the working directory.*/
int chdir(const char *path)
{
	int ret = syscall(40, path, 0, 0, 0,0);
	if(ret < 0)
	{
		errno = -ret;
		return -1;
	}
	return ret;
}

int fchdir(int fd)
{
	int ret = syscall(40, 0, fd, 0, 0, 0);
	if(ret < 0)
	{
		errno = -ret;
		return -1;
	}
	return ret;
}

int chmod(const char *p, mode_t m)
{
	int ret=syscall(100, (int)p, -1, m, 0, 0);
	if(ret < 0)
	{
		errno = -ret;
		return -1;
	}
	return ret;
}

int fchmod(int fd, mode_t m)
{
	int ret=syscall(100, 0, fd, m, 0, 0);
	if(ret < 0)
	{
		errno = -ret;
		return -1;
	}
	return ret;
}

int chown(const char *path, uid_t owner, gid_t group)
{
	int ret = syscall(112, path, -1, owner, group, 0);
	if(ret < 0)
	{
		errno = -ret;
		return -1;
	}
	return 0;
}

int fchown(int filedes, uid_t own, gid_t grp)
{
	int ret = syscall(112, 0, filedes, own, grp, 0);
	if(ret < 0)
	{
		errno = -ret;
		return -1;
	}
	return 0;
}

int chroot(const char *path)
{
	int ret = syscall(39, (int)path, 0, 0, 0, 0);
	if(ret < 0)
	{
		errno = -ret;
		return -1;
	}
	return ret;
}
