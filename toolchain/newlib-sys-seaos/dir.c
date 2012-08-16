#include <stdlib.h>
#include "./sys/dirent.h"
#include <errno.h>
#include <sys/stat.h>

int getdents (int fd, void *dp, int count)
{
	int ret = syscall(57, fd, (int)dp, count, 0, 0);
	if(ret < 0)
	{
		errno = -ret;
		return -1;
	}
	return ret;
}

DIR *opendir(const char *name)
{
	DIR *d = (DIR *)malloc(sizeof(DIR));
	if(*name == '/')
		strcpy(d->name, name);
	else {
		char *tmp = malloc(128);
		sprintf(d->name, "%s/%s", getcwd(tmp, 128), name);
		free(tmp);
	}
	d->pos=0;
	int res = open(d->name, 0, 0);
	if(res < 0) {
		free(d);
		return 0;
	}
	d->fd=res;
	return d;
}
/*
DIR *fdopendir(int fd)
{
	DIR *d = (DIR *)malloc(sizeof(DIR));
	int ret;
	if((ret=syscall(37, fd, d->name, 0, 0, 0)) < 0)
	{
		errno = -ret;
		free(d);
		return 0;
	}
	d->pos=0;
	d->fd=fd;
	return d;
}
*/
/* This really needs cleaning up */
struct dirent *readdir(DIR *d)
{
	errno=0;
	if(!d || d->fd < 0)
	{
		errno = EBADF;
		return 0;
	}
	char name[128];
	memset(name, 0, 128);
	struct stat statb;
	int ret = syscall(97, d->name, d->pos, name, &statb, 0);
	if(ret < 0) {
		if(ret != -ESRCH) 
			errno = -ret;
		return 0;
	}
	d->pos++;
	
	struct dirent *de = &d->__d;
	memset(de, 0, sizeof(*de));
	de->d_ino = statb.st_ino;
	if(S_ISCHR(statb.st_mode))
		de->d_type=3;
	else if(S_ISBLK(statb.st_mode))
		de->d_type=4;
	else if(S_ISREG(statb.st_mode))
		de->d_type=1;
	else if(S_ISDIR(statb.st_mode))
		de->d_type=2;
	else if(S_ISLNK(statb.st_mode))
		de->d_type=7;
	strcpy(de->d_name, name);
	de->d_reclen=strlen(name);
	return de;
}

int closedir(DIR *d)
{
	if(!d || d->fd < 0)
	{
		errno=EBADF;
		return -1;
	}
	close(d->fd);
	d->fd=-1;
	free(d);
	return 0;
}

/* Rewind DIRP to the beginning of the directory.  */
void rewinddir (DIR *d)
{
	if(!d || d->fd < 0)
	{
		errno=EBADF;
		return;
	}
	d->pos=0;
}

/* Seek to position POS on DIRP.  */
void seekdir (DIR *d, long int __pos){
	if(!d || d->fd < 0)
	{
		errno=EBADF;
		return;
	}
	d->pos = __pos;
}

/* Return the current position of DIRP.  */
long int telldir (DIR *d){
	if(!d || d->fd < 0)
	{
		errno=EBADF;
		return -1;
	}
	return d->pos;
}
