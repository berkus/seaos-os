#include "ksyscall.h"
#include <sys/types.h>
#include <sys/statfs.h>
//typedef signed long time_t;
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
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
int close (int fd)
{
	int ret = syscall(SYS_close, fd, 0, 0, 0, 0);
	if(ret < 0)
		errno=-ret;
	else
		return 0;
	return -1;
}

int fclean(FILE *f)
{
	return fflush(f);
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

extern char **environ;

#include <fcntl.h>
off_t lseek (
	int fd,
	off_t offset,
	int whence)
{
	int ret = syscall(SYS_lseek, fd, offset, whence, 0, 0);
	if(ret < 0) {
		errno = -ret;
		return -1;
	}
	return ret;
}



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

int unlink(
	const char * path)
{
	int ret = syscall(SYS_unlink, (int)path, 0, 0, 0, 0);
	if(ret < 0)
	{
		errno = -ret;
		return -1;
	}
	return ret;
}

int write (
	int fd,
	const void *buf,
	size_t nbytes)
{
	int ret = syscall(SYS_write, fd, (int)buf, nbytes, 0, 0);
	if(ret < 0)
	{
		errno = -ret;
		return -1;
	}
	return ret;
}

int read (
	int fd,
	void *buf,
	size_t nbytes)
{
	int ret = syscall(SYS_read, fd, (int)buf, nbytes, 0, 0);
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

int do_dup(int i, int f)
{
	int ret = syscall(16, i, f, 0, 0, 0);
	if(ret < 0)
	{
		errno = -ret;
		return -1;
	}
	return ret;
}
#if 1
int
dup2 (fd1, fd2)
     int fd1, fd2;
{
  int saved_errno, r;

  /* If FD1 is not a valid file descriptor, then return immediately with
     an error. */
  if (fcntl (fd1, F_GETFL, 0) == -1)
    return (-1);

  if (fd2 < 0 || fd2 >= getdtablesize ())
    {
      errno = EBADF;
      return (-1);
    }

  if (fd1 == fd2)
    return (0);

  saved_errno = errno;

  (void) close (fd2);
  r = fcntl (fd1, F_DUPFD, fd2);

  if (r >= 0)
    errno = saved_errno;
  else
    if (errno == EINVAL)
      errno = EBADF;

  /* Force the new file descriptor to remain open across exec () calls. */
  //SET_OPEN_ON_EXEC (fd2);
  return (r);
}
#endif
int dup(int i)
{
	return do_dup(i, 0);
}

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

int ftruncate(int f, off_t len)
{
	int ret = syscall(110, f, len, 0, 0, 0);
	if(ret < 0)
	{
		errno = -ret;
		return -1;
	}
	return 0;
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

int truncate(const char *p, off_t len)
{
	int f = open(p, O_RDWR, 0);
	if(f < 0) return -1;
	int res =  ftruncate(f, len);
	close(f);
	return res;
}

#include <sys/fcntl.h>
int unlinkat(int fd,
      const  char * path, int flags)
{
	char *newpath = (char *)malloc(1024);
	if(!newpath) {
		errno = ENOMEM;
		return -1;
	}
	if(path[0] != '/' && fd >= 0) {
		int ret;
		if((ret=syscall(37, fd, (int)newpath, 0, 0, 0)) < 0) {
			errno = -ret;
			free(newpath);
			return -1;
		}
		if(newpath[strlen(newpath)-1] != '/')
			strcat(newpath, "/");
		strcat(newpath, path);
	} else {
		strcpy(newpath, path);
	}
	if(flags & AT_REMOVEDIR)
		rmdir(newpath);
	else
		unlink(newpath);
	free(newpath);
	return 0;
}

int mkdir(const char *argv, mode_t mode)
{
	char tmp[strlen(argv) + 2];
	memset(tmp, 0, strlen(argv) + 2);
	strcpy(tmp, argv);
	strcat(tmp, "/");
	int ret = open(tmp, O_CREAT | O_EXCL, mode);
	if(ret < 0)
		return -1;
	else
		close(ret);
	return 0;
}

int creat(const char *p, mode_t mode)
{
	int ret = open(p, O_WRONLY|O_CREAT|O_TRUNC, mode);
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

int makedev(int maj, int min)
{
	#define GETDEV(maj, min) (maj*256+min)
	return GETDEV(maj, min);
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


/* Get the pathname of the current working directory,
   and put it in SIZE bytes of BUF.  Returns NULL if the
   directory couldn't be determined or SIZE was too small.
   If successful, returns BUF.  In GNU, if BUF is NULL,
   an array is allocated with `malloc'; the array is SIZE
   bytes long, unless SIZE <= 0, in which case it is as
   big as necessary.  */
#include <sys/dirent.h>
__attribute__ ((weak)) char *getcwd (char *buf, size_t size)
{
	errno = 0;
	if(buf && !size) {
		errno = EINVAL;
		return 0;
	}
	
	if(!buf) {
		if(!size)size = 1024;
		buf = (char *)malloc(size);
	}
	
	memset(buf, 0, size);
	
	int ret = syscall(36, buf, size, 0, 0, 0);
	if(ret < 0) {
		errno = -ret;
		return 0;
	}
	return buf;
}


int rmdir(const char *b)
{
	int ret= syscall(53,(int) b, 0, 0, 0, 0);
	if(ret < 0)
	{
		errno = -ret;
		return -1;
	}
	return ret;
}

int link(const char *path1, const char *path2)
{
	int ret= syscall(33, (int)path1, (int)path2, 0, 0, 0);
	if(ret < 0)
	{
		errno = -ret;
		return -1;
	}
	return ret;
}

int
mkfifo (path, mode)
     const char *path;
     mode_t mode;
{

  return (mknod (path, ((mode&0xFFF) | S_IFIFO), 0));

}

int _link(const char *path1, const char *path2)
{
	return link(path1, path2);
}
int _syslink(const char *path1, const char *path2)
{
	return link(path1, path2);
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

ssize_t readlink(const char * path, char * buf, size_t bufsize)
{
	int ret= syscall(107, (int)path, (int)buf, bufsize, 0, 0);
	if(ret < 0)
	{
		errno = -ret;
		return -1;
	}
	return ret;
}

int symlink(const char *p1, const char *p2)
{
	int ret=syscall(106, (int)p1, (int)p2, 0, 0, 0);
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

int fdatasync(int file)
{
	return fsync(file);
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
