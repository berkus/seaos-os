#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include "ksyscall.h"
#include <sys/dirent.h>
int optreset=0;

int sea_mount_filesystem(char *node, char *dir, char *fsname, char *opts, int flags)
{
	int ret = syscall(SYS_MOUNT2, node, dir, fsname, opts, flags);
	if(ret < 0)
		errno = -ret;
	return ret;
}

int __seaos_is_good__()
{
	return 1;
}
#include <sys/reboot.h>
void kernel_reset(void)
{
	syscall(SYS_KRESET, RB_AUTOBOOT,0,0,0,0);
}

void kernel_shutdown(void)
{
	syscall(SYS_KPOWOFF, 0,0,0,0,0);
}

int reboot(int __howto)
{
	int ret = syscall(SYS_KRESET, __howto, 0, 0, 0, 0);
	if(ret < 0)
	{
		errno = -ret;
		return -1;
	}
	return ret;
}

int sea_umount_filesystem(char *dir, int flags)
{
	int ret = syscall(SYS_UMOUNT, dir, flags, 0, 0, 0);
	if(ret < 0) {
		errno = -ret;
		return -1;
	}
	return ret;
}

int mem_stat(struct mem_stat *s)
{
	int ret = syscall(SYS_MEMSTAT, (int)s, 0, 0, 0, 0);
	if(ret < 0) {
		errno = -ret;
		return -1;
	}
	return ret;
}

int sigsetjmp(void *a, int x)
{
	return setjmp(a);
}

int siglongjmp(void *a, int x)
{
	return longjmp(a);
}


int sea_load_module(char *path, char *opts, int flags)
{
	int ret = syscall(SYS_LMOD, (int)path, opts, flags, 0, 0);
	if(ret < 0) {
		errno = -ret;
		return -1;
	}
	return ret;
}

int sys_syslog(int level, char *buf, int len)
{
	int ret = syscall(120, level, buf, len, 0, 0);
	if(ret < 0)
	{
		errno=-ret;
		return -1;
	}
	return ret;
}

#include <limits.h>
#include <stdarg.h>
void syslog(int lev, const char *fmt, ...)
{
  int ret;
  va_list ap;
  FILE f;
  char str[256];
  f._flags = __SWR | __SSTR;
  f._bf._base = f._p = (unsigned char *) str;
  f._bf._size = f._w = INT_MAX;
  f._file = -1;  /* No file. */
  va_start (ap, fmt);
  ret = _svfprintf_r (_REENT, &f, fmt, ap);
  va_end (ap);
  *f._p = '\0';	/* terminate the string */
  sys_syslog(lev, str, strlen(str));
}

void openlog(const char *i, int o, int f)
{
	syscall(120, o, i, f, 1, 0);
}

void closelog(void)
{
	syscall(120, 0, 0, 0, 2, 0);
}

void setlogmask(int mask)
{
	syscall(120, mask, 0, 0, 3, 0);
}

int sea_unload_module(char *path, int flags)
{
	int ret = syscall(SYS_ULMOD, (int)path, flags, 0, 0, 0);
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

#include <sys/utsname.h>
int uname(struct utsname *name)
{
	int ret = syscall(116, (int)name, 0, 0, 0, 0);
	if(ret < 0) {
		errno = -ret;
		return -1;
	}
	return ret;
}
