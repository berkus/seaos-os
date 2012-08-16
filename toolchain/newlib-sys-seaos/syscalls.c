#include "ksyscall.h"
#include <sys/stat.h>

int syscall(int num, int a, int b, int c, int d, int e)
{
	errno = 0;
	int x;
	//char tmp[64];
	//memset(tmp, 0, 63);
	//sprintf(tmp, "<%d> ", num);
	//asm volatile("int $0x80":"=a"(x):"0" (5), "b" ((int)1), "c" ((int)tmp), "d" ((int)strlen(tmp)), "S" ((int)0), "D" ((int)0));
	__asm__ __volatile__("int $0x80":"=a"(x):"0" (num), "b" ((int)a), "c" ((int)b), "d" ((int)c), "S" ((int)d), "D" ((int)e));

	return x;
}

int open (
	const char *buf,
	int flags,
	mode_t mode)
{
	int ret = syscall(SYS_open, (int)buf, flags, mode, 0, 0);
	if(ret < 0) {
		errno = -ret;
		return -1;
	}
	return ret;
}

long sysconf(int n)
{
	long ret = syscall(59, n, 0, 0, 0, 0);
	if(ret < 0) {
		errno = EINVAL;
		return -1;
	}
	return ret;
}

int ioctl(int fp, int cmd, int arg)
{
	int ret = syscall(SYS_IOCTL, fp, cmd, arg, 0, 0);
	if(ret < 0) {
		errno = -ret;
		return -1;
	}
	return ret;
}
