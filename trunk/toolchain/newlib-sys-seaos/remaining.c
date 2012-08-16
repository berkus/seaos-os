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

int getdtablesize()
{
	return 10000000;
}

int getgroups(int gidsetsize, gid_t grouplist[])
{
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
#include <fcntl.h>
int daemon(int nochdir, int noclose)
{
	int fr = fork();
	if(fr < 0)
	{
		/* errno is set by fork */
		return -1;
	}
	/* parent exits */
	if(fr)
		exit(0);
	fflush(0);
	if(!noclose) {
		fclose(stdin);
		fclose(stdout);
		fclose(stderr);
	}
	if(!nochdir)
		chdir("/");
	int f = open("/dev/tty0", O_RDONLY, 0);
	if(f >= 0) {
		ioctl(f, 2, 0);
		close(f);
	}
	setsid();
	umask(0);
	int i = open("/dev/null", O_RDONLY);
	int o = open("/dev/null", O_RDWR);
	int e = open("/dev/null", O_RDWR);
	if(i > 0)
		close(i);
	if(o > 1 || !o)
		close(i);
	if(e > 2 || !e || e == 1)
		close(e);
	errno=0;
	return 0;
}

int getpgrp()
{
	/* TODO: */
	return getgid();
}

int setpgid(pid_t a, pid_t b)
{
	int ret = syscall(61, a, b, 0, 0, 0);
	if(ret < 0)
	{
		errno=-ret;
		return -1;
	}
	return ret;
}

int setpgrp()
{
	return setpgid(0,0);
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
#define va_list char *
#define __va_rounded_size(TYPE)  \
  (((sizeof (TYPE) + sizeof (int) - 1) / sizeof (int)) * sizeof (int))

#ifndef __sparc__
#define va_start(AP, LASTARG) 						\
 (AP = ((char *) &(LASTARG) + __va_rounded_size (LASTARG)))
#else
#define va_start(AP, LASTARG) 						\
 (__builtin_saveregs (),						\
  AP = ((char *) &(LASTARG) + __va_rounded_size (LASTARG)))
#endif

#define va_end(AP)

#define va_arg(AP, TYPE)						\
 (AP += __va_rounded_size (TYPE),					\
  *((TYPE *) (AP - __va_rounded_size (TYPE))))

int fcntl(int des, int cmd, ...)
{
	va_list args;
	va_start(args, cmd);
	
	int ret = syscall(101, des, cmd, va_arg(args, int), 0, 0);
	
	va_end(args);
	if(ret < 0) {
		errno = -ret;
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

int rpmatch(char *i)
{
	if(*(i) == 'y' || *(i) == 'Y')
		return 1;
	if((*(i) == 'o' || *i == 'O') && (*i=='k' || *i=='K'))
		return 1;
	return 0;
}

int getgrgid()
{
	return 0;
}

void endgrent()
{
	
}

void setgrent()
{
	
}

void getgrent()
{
	
}

#include <netdb.h>
struct hostent ___internal_hostent;
struct hostent *gethostbyaddr(const void *addr, socklen_t len, int type)
{
	int ret = syscall(117, (int)&___internal_hostent, (int)addr, (int)len, type, 0);
	if(ret < 0)
	{
		errno = -ret;
		return 0;
	}
	return &___internal_hostent;
}

struct hostent *gethostbyname(const char *name)
{
	int ret = syscall(117, (int)&___internal_hostent, 0, 0, 0, (int)name);
	if(ret < 0)
	{
		errno = -ret;
		return 0;
	}
	return &___internal_hostent;
}

void endservent(void)
{
	syscall(119, 0, 0, 0, 0, 0);
}

struct servent ___internal_servent;
struct servent *getservbyname(const char *name, const char *proto)
{
	int ret = syscall(118, 0, name, proto, (int)&___internal_servent, 0);
	if(ret < 0)
	{
		errno = -ret;
		return 0;
	}
	return &___internal_servent;
}

struct servent *getservbyport(int port, const char *proto)
{
		int ret = syscall(118, port, 0, proto, (int)&___internal_servent, 0);
	if(ret < 0)
	{
		errno = -ret;
		return 0;
	}
	return &___internal_servent;
}

struct servent *getservent(void)
{
	int ret = syscall(118, 0, 0, 0, (int)&___internal_servent, 0);
	if(ret < 0)
	{
		errno = -ret;
		return 0;
	}
	return &___internal_servent;
}

void setservent(int stayopen)
{
	syscall(119, 1, stayopen, 0, 0, 0);
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

unsigned long   htonl (unsigned long a){return a;}
unsigned short  htons (unsigned short a){return a;}
unsigned long   ntohl (unsigned long a){return a;}
unsigned short  ntohs (unsigned short a){return a;}

int getgrnam()
{
	return 0;
}

char *___AAAgetwd(char *b)
{
	int ret = syscall(36, b, 0, 0, 0, 0);
	return b;
}

char *gai_strerror(int code)
{
	return "unknown error";
}

int gethostname(char *name, size_t len)
{
	int ret = syscall(114, name, len, 0, 0, 0);
	if(ret < 0)
	{
		errno = -ret;
		return -1;
	}
	return 0;
}

#define	_U	01
#define	_L	02
#define	_N	04
#define	_S	010
#define _P	020
#define _C	040
#define _X	0100
#define	_B	0200
#define _CTYPE_DATA_0_127 \
_C,	_C,	_C,	_C,	_C,	_C,	_C,	_C, \
_C,	_C|_S, _C|_S, _C|_S,	_C|_S,	_C|_S,	_C,	_C, \
_C,	_C,	_C,	_C,	_C,	_C,	_C,	_C, \
_C,	_C,	_C,	_C,	_C,	_C,	_C,	_C, \
_S|_B,	_P,	_P,	_P,	_P,	_P,	_P,	_P, \
_P,	_P,	_P,	_P,	_P,	_P,	_P,	_P, \
_N,	_N,	_N,	_N,	_N,	_N,	_N,	_N, \
_N,	_N,	_P,	_P,	_P,	_P,	_P,	_P, \
_P,	_U|_X,	_U|_X,	_U|_X,	_U|_X,	_U|_X,	_U|_X,	_U, \
_U,	_U,	_U,	_U,	_U,	_U,	_U,	_U, \
_U,	_U,	_U,	_U,	_U,	_U,	_U,	_U, \
_U,	_U,	_U,	_P,	_P,	_P,	_P,	_P, \
_P,	_L|_X,	_L|_X,	_L|_X,	_L|_X,	_L|_X,	_L|_X,	_L, \
_L,	_L,	_L,	_L,	_L,	_L,	_L,	_L, \
_L,	_L,	_L,	_L,	_L,	_L,	_L,	_L, \
_L,	_L,	_L,	_P,	_P,	_P,	_P,	_C

#define _CTYPE_DATA_128_255 \
0,	0,	0,	0,	0,	0,	0,	0, \
0,	0,	0,	0,	0,	0,	0,	0, \
0,	0,	0,	0,	0,	0,	0,	0, \
0,	0,	0,	0,	0,	0,	0,	0, \
0,	0,	0,	0,	0,	0,	0,	0, \
0,	0,	0,	0,	0,	0,	0,	0, \
0,	0,	0,	0,	0,	0,	0,	0, \
0,	0,	0,	0,	0,	0,	0,	0, \
0,	0,	0,	0,	0,	0,	0,	0, \
0,	0,	0,	0,	0,	0,	0,	0, \
0,	0,	0,	0,	0,	0,	0,	0, \
0,	0,	0,	0,	0,	0,	0,	0, \
0,	0,	0,	0,	0,	0,	0,	0, \
0,	0,	0,	0,	0,	0,	0,	0, \
0,	0,	0,	0,	0,	0,	0,	0, \
0,	0,	0,	0,	0,	0,	0,	0

char _ctype_b[128 + 256] = {
	_CTYPE_DATA_128_255,
	_CTYPE_DATA_0_127,
	_CTYPE_DATA_128_255
};



char *__ctype_ptr = (char *)(_ctype_b+127);
//char *__ctype_ptr__ = (char *)(_ctype_b+127);
