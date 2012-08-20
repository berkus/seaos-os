#include "ksyscall.h"
#include <sys/types.h>
#include <sys/statfs.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
int fchdir(int filedes)
{
	char *name = (char *)malloc(1024);
	int ret;
	ret = syscall(37, filedes, name, 0, 0, 0);
	if(ret < 0)
	{
		free(name);
		errno=-ret;
		return -1;
	}
	ret = chdir(name);
	free(name);
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
	int ret=syscall(100, (int)0, fd, m, 0, 0);
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
