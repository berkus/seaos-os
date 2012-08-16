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

#define LINUX_LINK_MAX	127

static long int posix_pathconf (const char *path, int name);


/* Get file-specific information about descriptor FD.  */
long int
pathconf (path, name)
     const char *path;
     int name;
{
  if (name == _PC_LINK_MAX)
    {

	    return LINUX_LINK_MAX;

    }

  return posix_pathconf (path, name);
}
long fpathconf(int fd, int m)
{
	char *name = (char *)malloc(1024);
	syscall(37, fd, name, 0, 0, 0);
	int ret = pathconf(name, m);
	free(name);
	return ret;
}
/* Get file-specific information about PATH.  */
static long int
posix_pathconf (const char *path, int name)
{
  if (path[0] == '\0')
    {
      errno= (ENOENT);
      return -1;
    }

  switch (name)
    {
    default:
     errno= (EINVAL);
      return -1;

    case _PC_LINK_MAX:
#ifdef	LINK_MAX
      return LINK_MAX;
#else
      return -1;
#endif

    case _PC_MAX_CANON:
#ifdef	MAX_CANON
      return MAX_CANON;
#else
      return -1;
#endif

    case _PC_MAX_INPUT:
#ifdef	MAX_INPUT
      return MAX_INPUT;
#else
      return -1;
#endif

    case _PC_NAME_MAX:
#ifdef	NAME_MAX
      {
	struct statfs buf;
	int save_errno = errno;

	if (__statfs (path, &buf) < 0)
	  {
	    if (errno == ENOSYS)
	      {
		errno = save_errno;
		return NAME_MAX;
	      }
	    return -1;
	  }
	else
	  {
#ifdef _STATFS_F_NAMELEN
	    return buf.f_namelen;
#else
# ifdef _STATFS_F_NAME_MAX
	    return buf.f_name_max;
# else
	    return NAME_MAX;
# endif
#endif
	  }
      }
#else
      return -1;
#endif

    case _PC_PATH_MAX:
#ifdef	PATH_MAX
      return PATH_MAX;
#else
      return -1;
#endif

    case _PC_PIPE_BUF:
#ifdef	PIPE_BUF
      return PIPE_BUF;
#else
      return -1;
#endif

    case _PC_CHOWN_RESTRICTED:
#ifdef	_POSIX_CHOWN_RESTRICTED
      return _POSIX_CHOWN_RESTRICTED;
#else
      return -1;
#endif

    case _PC_NO_TRUNC:
#ifdef	_POSIX_NO_TRUNC
      return _POSIX_NO_TRUNC;
#else
      return -1;
#endif

    case _PC_VDISABLE:
#ifdef	_POSIX_VDISABLE
      return _POSIX_VDISABLE;
#else
      return -1;
#endif

    case _PC_SYNC_IO:
#ifdef	_POSIX_SYNC_IO
      return _POSIX_SYNC_IO;
#else
      return -1;
#endif

    case _PC_ASYNC_IO:
#ifdef	_POSIX_ASYNC_IO
      {
	/* AIO is only allowed on regular files and block devices.  */
	struct stat64 st;

	if (stat64 (path, &st) < 0
	    || (! S_ISREG (st.st_mode) && ! S_ISBLK (st.st_mode)))
	  return -1;
	else
	  return 1;
      }
#else
      return -1;
#endif

    case _PC_PRIO_IO:
#ifdef	_POSIX_PRIO_IO
      return _POSIX_PRIO_IO;
#else
      return -1;
#endif



    case _PC_FILESIZEBITS:
#ifdef FILESIZEBITS
      return FILESIZEBITS;
#else
      /* We let platforms with larger file sizes overwrite this value.  */
      return 32;
#endif




    case _PC_SYMLINK_MAX:
      /* In general there are no limits.  If a system has one it should
	 overwrite this case.  */
      return -1;
    }
}
