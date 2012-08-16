#ifndef SYSCALL_H
#define SYSCALL_H
#define SYS_SETUP  0
#define SYS_EXIT   1
#define SYS_FORK   2
#define SYS_WAIT   3
#define SYS_READ   4
#define SYS_WRITE  5 
#define SYS_OPEN   6
#define SYS_CLOSE  7
#define SYS_FSTAT  8
#define SYS_STAT   9
#define SYS_ISATTY 10
#define SYS_SEEK   11
#define SYS_SIGNAL 12
#define SYS_SBRK   13
#define SYS_TIMES  14
#define SYS_DUP    15
#define SYS_DUP2   16
#define SYS_IOCTL  17
#define SYS_SANITY 18
#define SYS_DFSCN  19 /* Create devfs node */
#define SYS_DFSRN  20 /* Remove dfs node */
#define SYS_PFSCN  21
#define SYS_CREATE_PFS 22
#define SYS_PFSREAD 23
#define SYS_PFSWRITE 24
#define SYS_GETFP  25
#define SYS_EXECVE 26
#define SYS_LMOD   27
#define SYS_ULMOD  28
#define SYS_CANUNLOAD 29
#define SYS_ULALLMODS 30
#define SYS_GETPID  31
#define SYS_GETPPID 32

#define SYS_LINK   33
#define SYS_UNLINK 34
#define SYS_GETREFCOUNT 35
#define SYS_GETPWD 36
#define SYS_GETPATH 37
#define SYS_RENAME 38
#define SYS_CHROOT 39
#define SYS_CHDIR  40
#define SYS_MOUNT  41
#define SYS_UMOUNT 42
#define SYS_READDIR 43
#define SYS_CREATE 44
#define SYS_CREATE_CONSOLE 45
#define SYS_SWITCH_CONSOLE 46
#define SYS_FSSTAT     47
#define SYS_MKFIFO1 48
#define SYS_PIPE1 49
#define SYS_MMAP 50
#define SYS_MUNMAP 51
#define SYS_SYNC 52
#define SYS_RMDIR 53
#define SYS_FSYNC 54
#define SYS_ALARM 55
#define SYS_SELECT 56
#define SYS_TTYNAME 57
#define SYS_IPUT 58
#define SYS_SYSCONF 59

#define SYS_WAITFLAG 65
#define SYS_WAITFLAG_EXC 66
#define SYS_SCHEDULE 67
#define SYS_TSTAT    68
#define SYS_WAITINT  69
#define SYS_WAITIRQ  70
#define SYS_DELAY    71
#define SYS_KRESET   72
#define SYS_KPOWOFF  73
#define SYS_GETUID   74
#define SYS_GETGID   75
#define SYS_SETUID   76
#define SYS_SETGID   77
#define SYS_MEMSTAT  78
#define SYS_TPSTAT   79
#define SYS_MOUNT2   80
#define SYS_GETPATHINO 81

#define SYS_MKFIFO 82
#define SYS_PIPE   83
#define SYS_SETSIG 84

#define SYS_CRMSG  85
#define SYS_SNMSG  86
#define SYS_GTMSG  87
#define SYS_FRMSG  88
#define SYS_GETTIME 89
#define SYS_TIMERTH 90
#define SYS_ISSTATE 91
#define SYS_WAIT3 92

#define SYS_FREEZE 93
#define SYS_MELT 94

#define SYS_SIGACT 98



#define	SYS_exit	1
#define	SYS_open	6
#define	SYS_close	7
#define	SYS_read	4
#define	SYS_write	5
#define	SYS_lseek	11
#define	SYS_unlink	34
#define	SYS_getpid	31
#define	SYS_kill	12
#define SYS_fstat       8
#define SYS_sbrk	13
#include <errno.h>
/* ARGV support.  */
//#define SYS_argvlen	12
//#define SYS_argv	13

/* These are extras added for one reason or another.  */
#define SYS_chdir	 41
#define SYS_stat	 9
//#define SYS_chmod 	 16
//#define SYS_utime 	 17
//#define SYS_time 	 18
//#define SYS_gettimeofday 19
#define SYS_isatty 10
#define SYS_times	 14
#define SYS_link	 33
#endif