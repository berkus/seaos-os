#include "ksyscall.h"
#include <signal.h>
int kill(
        int pid,
        int sig)
{
  int ret = syscall(SYS_kill, pid, sig, 0, 0, 0);
  if(ret < 0) {
	  errno = -ret;
	  return -1;
  }
  return ret;
}

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

int sigaction(int sig, const struct sigaction *act, struct sigaction *oact) {
	int ret = syscall(98, sig, (int)act, (int)oact, 0, 0);
	if(ret < 0) {
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

pid_t setsid()
{
	int ret = syscall(60, 0, 0, 0, 0, 0);
	if(ret < 0) {
		errno=-ret;
		return -1;
	}
	return ret;
}

pid_t getsid(pid_t p)
{
	int ret = syscall(60, 1, p, 0, 0, 0);
	if(ret < 0) {
		errno=-ret;
		return -1;
	}
	return ret;
}

pid_t vfork(void)
{
	pid_t pid;
	
	pid = fork();
	
	if(!pid)
	{
		/* In child. */
		return 0;
	}
	else
	{
		/* In parent.  Wait for child to finish. */
		if (waitpid (pid, NULL, 0) < 0)
			return pid;
	}
}

void _exit(int z)
{
	syscall(SYS_exit, z, 0, 0, 0, 0);
	for(;;);
}

void __exit(int z)
{
	return _exit(z);
}
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
#include <stdio.h>
int fork()
{
	int ret = syscall(2, 0, 0, 0, 0, 0);
	if(ret < 0) {
		errno = -ret;
		return -1;
	}
	return ret;
}

int
sbrk (nbytes)
int nbytes;
{
	int ret = syscall(SYS_sbrk, nbytes, 0, 0, 0, 0);
	if(ret < 0) {
		errno = -ret;
		return -1;
	}
	return ret;
}

int getpid()
{
	int ret = syscall(31, 0, 0, 0, 0, 0);
	if(ret < 0) {
		errno = -ret;
		return -1;
	}
	return ret;
}

uid_t get_uid()
{
	return syscall(SYS_GETUID, 0,0,0,0,0);
}

uid_t getuid()
{
	return get_uid();
}


uid_t geteuid()
{
	return syscall(SYS_GETUID, 0,0,0,0,0);
}

gid_t get_gid()
{
	return syscall(SYS_GETGID, 0,0,0,0,0);
}

int set_uid(int n)
{
	int ret = syscall(SYS_SETUID, n,0,0,0,0);
	if(ret < 0) {
		errno = -ret;
		return -1;
	}
	return ret;
}

gid_t set_gid(int n)
{
	int ret = syscall(SYS_SETGID, n,0,0,0,0);
	if(ret < 0) {
		errno = -ret;
		return -1;
	}
	return ret;
}

int setreuid(uid_t r, uid_t e)
{
	int ret = syscall(SYS_SETUID, r,e,0,0,0);
	if(ret < 0) {
		errno = -ret;
		return -1;
	}
	return ret;
}

int setregid(gid_t r, gid_t e)
{
	int ret = syscall(SYS_SETGID, r,e,0,0,0);
	if(ret < 0) {
		errno = -ret;
		return -1;
	}
	return ret;
}

gid_t getgid()
{
	return get_gid();
}

gid_t getegid()
{
	return syscall(SYS_GETGID, 0,0,0,0,0);
}

int setuid(uid_t n)
{
	return set_uid(n);
}

int setgid(gid_t n)
{
	return set_gid(n);
}

int getppid()
{
	return syscall(SYS_GETPPID, 0, 0, 0, 0, 0);
}

int waitagain()
{
	return syscall(127, 0, 0, 0, 0, 0);
}
