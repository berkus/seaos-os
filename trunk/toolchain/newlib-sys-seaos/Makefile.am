AUTOMAKE_OPTIONS = cygnus
INCLUDES = $(NEWLIB_CFLAGS) $(CROSS_CFLAGS) $(TARGET_CFLAGS) -I ./include -I ./include/netinet
AM_CCASFLAGS = $(INCLUDES)
noinst_LIBRARIES = lib.a
if MAY_SUPPLY_SYSCALLS
extra_objs = $(lpfx)syscalls.o mmap.o cfspeed.o rand.o rand48.o rand_r.o seaos.o termios.o pathconf.o dir.o time.o proc.o fs.o signal.o setjmp.o remaining.o execl.o execle.o execlp.o execv.o execve.o execvp.o ftok.o
else
extra_objs =
endif
lib_a_SOURCES =
lib_a_LIBADD = $(extra_objs)
EXTRA_lib_a_SOURCES = cfspeed.c syscalls.c mmap.c rand.c rand48.c rand_r.c seaos.c termios.c pathconf.c dir.c time.c proc.c fs.c crt0.c signal.c setjmp.S remaining.c execl.c execle.c execlp.c execv.c execve.c execvp.c ftok.c
lib_a_DEPENDENCIES = $(extra_objs)
lib_a_CCASFLAGS = $(AM_CCASFLAGS)
lib_a_CFLAGS = $(AM_CFLAGS) -I ./include -I ./include/netinet
if MAY_SUPPLY_SYSCALLS
all: crt0.o
endif
ACLOCAL_AMFLAGS = -I ../../..
CONFIG_STATUS_DEPENDENCIES = $(newlib_basedir)/configure.host
