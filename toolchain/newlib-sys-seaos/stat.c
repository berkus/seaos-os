#include "ksyscall.h"
#include <sys/types.h>
#include <sys/statfs.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>
struct kstat {
	unsigned short	st_dev;
	unsigned long	st_ino;
	unsigned short	st_mode;
	unsigned short	st_nlink;
	unsigned short	st_uid;
	unsigned short	st_gid;
	unsigned short	st_rdev;
	unsigned long	st_size;
	unsigned long	st_blksize;
	unsigned long	st_blocks;
		time_t	st_atime;
  long		st_spare1;
  time_t	st_mtime;
  long		st_spare2;
  time_t	st_ctime;
};

int mem_stat(struct mem_stat *s)
{
	int ret = syscall(SYS_MEMSTAT, (int)s, 0, 0, 0, 0);
	if(ret < 0) {
		errno = -ret;
		return -1;
	}
	return ret;
}

int task_stat(unsigned p, struct task_stat *s)
{
	int ret = syscall(SYS_TSTAT, (int)p, (int)s, 0, 0, 0);
	if(ret < 0) {
		errno=-ret;
		return -1;
	}
	return ret;
}

int select (int n, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
            struct timeval *timeout)
{
  int ret = syscall(56, n, readfds, writefds, exceptfds, timeout);
  if(ret < 0) {
	  errno = -ret;
	  return -1;
  }
  return ret;
}

int get_nodestr(char *path, char *node)
{
	int ret = syscall(111, path, node, 0, 0, 0);
	if(ret < 0)
	{
		errno = -ret;
		return -1;
	}
	return 0;
}

int access(const char *path, int mode)
{
	int ret = syscall(99, (int)path, mode, 0, 0, 0);
	if(ret < 0)
	{
		errno = -ret;
		return -1;
	}
	return ret;
}

int __fxstat(int ver, int fd, struct stat *buf)
{
	return fstat(fd, buf);
}
/*
int isatty(int fd)
{
	int ret = syscall(SYS_isatty, fd, 0, 0, 0, 0);
	if(ret < 0)
	{
		errno = -ret;
		return -1;
	}
	return ret;
}
*/
int stat(
	const char *path,
	 struct stat *buf)
{
	
	struct kstat k;
	int ret= syscall(SYS_stat, (int)path, (int)&k, 0, 0, 0);
	if(ret < 0)
	{
		errno = -ret;
		return -1;
	}
	buf->st_dev = k.st_dev;
	buf->st_ino = k.st_ino;
	buf->st_mode = k.st_mode;
	buf->st_nlink = k.st_nlink;
	buf->st_uid = k.st_uid;
	buf->st_gid = k.st_gid;
	buf->st_rdev = k.st_rdev;
	buf->st_size = k.st_size;
	buf->st_blksize = k.st_blksize;
	buf->st_blocks = k.st_blocks;
	buf->st_atime = k.st_atime;
	buf->st_mtime = k.st_mtime;
	buf->st_ctime = k.st_ctime;
	return ret;
	
}

int lstat(
	const char *path,
	 struct stat *buf)
{
	struct kstat k;
	int ret= syscall(SYS_stat, (int)path, (int)&k, 1, 0, 0);
	if(ret < 0)
	{
		errno = -ret;
		return -1;
	}
	buf->st_dev = k.st_dev;
	buf->st_ino = k.st_ino;
	buf->st_mode = k.st_mode;
	buf->st_nlink = k.st_nlink;
	buf->st_uid = k.st_uid;
	buf->st_gid = k.st_gid;
	buf->st_rdev = k.st_rdev;
	buf->st_size = k.st_size;
	buf->st_blksize = k.st_blksize;
	buf->st_blocks = k.st_blocks;
	buf->st_atime = k.st_atime;
	buf->st_mtime = k.st_mtime;
	buf->st_ctime = k.st_ctime;
	return ret;
	
}

int statfs(const char *path, struct statfs *buf)
{
	errno=0;
	int r = open(path, O_RDONLY, 0);
	if(r < 0) return -1;
	int ret = fstatfs(r, buf);
	int _e = errno;
	close(r);
	errno = _e;
	return ret;
}

int statvfs(const char *path, struct statfs *buf)
{
	return statfs(path, buf);
}

int fstatvfs(int fd, struct statfs *buf)
{
	return fstatfs(fd, buf);
}

int fstatfs(int fd, struct statfs *buf)
{
	int ret = syscall(121, fd, (int)buf, 0, 0, 0);
	if(ret < 0) {
		errno = -ret;
		return -1;
	}
	return ret;
}


int fstat(int fd, struct stat *buf)
{
	struct kstat k;
	int ret= syscall(SYS_fstat, fd, (int)&k, 0, 0, 0);
	if(ret < 0)
	{
		errno = -ret;
		return -1;
	}
	buf->st_dev = k.st_dev;
	buf->st_ino = k.st_ino;
	buf->st_mode = k.st_mode;
	buf->st_nlink = k.st_nlink;
	buf->st_uid = k.st_uid;
	buf->st_gid = k.st_gid;
	buf->st_rdev = k.st_rdev;
	buf->st_size = k.st_size;
	buf->st_blksize = k.st_blksize;
	buf->st_blocks = k.st_blocks;
	buf->st_atime = k.st_atime;
	buf->st_mtime = k.st_mtime;
	buf->st_ctime = k.st_ctime;
	return ret;
}
