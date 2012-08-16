#include <utime.h>
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
clock_t times(struct tms *b)
{
	int ret = syscall(14, (int)b, 0, 0, 0, 0);
	if(ret < 0) {
		errno = -ret;
		return -1;
	}
	return ret;
}

int get_timer_ticks_hz()
{
	return syscall(90, 0, 0, 0, 0, 0);
}

int gettimeofday(struct timeval *tv, void *g)
{
	unsigned p;
	unsigned hz = syscall(90, &p, 0, 0, 0, 0);
	struct tm t;
	syscall(89, (int)&t, 0, 0, 0, 0);
	tv->tv_sec = t.tm_sec + t.tm_min*60 + t.tm_hour*60*60;
	tv->tv_usec=(p % hz)*1000;
	return 0;
}

int utime(const char *path, const struct utimbuf *times)
{
	int ret = syscall(113, path, times ? times->actime : 0, times ? times->modtime : 0, 0, 0);
	if(ret < 0) {
		errno = -ret;
		return -1;
	}
	return 0;
}

void delay(int t)
{
	syscall(71, t,0,0,0,0);
}

unsigned sleep(unsigned s)
{
	delay(s * get_timer_ticks_hz());
}
