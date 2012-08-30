#include "ksyscall.h"
#include <sys/types.h>
#include <sys/statfs.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
int unlinkat(int fd, const  char * path, int flags)
{
	char *newpath = (char *)malloc(1024);
	if(!newpath) {
		errno = ENOMEM;
		return -1;
	}
	if(path[0] != '/' && fd >= 0) {
		int ret;
		if((ret=syscall(37, fd, (int)newpath, 1024-(strlen(path)+2), 0, 0)) < 0) {
			errno = -ret;
			free(newpath);
			return -1;
		}
		/* lets make sure that we append properly.
		 * If fd doesn't point to a directory, then this
		 * wont make sense. But fuck it, we'll just error out later */
		if(newpath[strlen(newpath)-1] != '/')
			strcat(newpath, "/");
		strcat(newpath, path);
	} else
		strcpy(newpath, path);
	if(flags & AT_REMOVEDIR)
		rmdir(newpath);
	else
		unlink(newpath);
	free(newpath);
	return 0;
}
