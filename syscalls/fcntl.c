/*
 * SYSCALL_DEFINE3(fcntl, unsigned int, fd, unsigned int, cmd, unsigned long, arg)
 *
 * For a successful call, the return value depends on the operation:
 *
 *     F_DUPFD The new descriptor.
 *     F_GETFD Value of file descriptor flags.
 *     F_GETFL Value of file status flags.
 *     F_GETLEASE Type of lease held on file descriptor.
 *     F_GETOWN Value of descriptor owner.
 *     F_GETSIG Value of signal sent when read or write becomes possible, or zero for traditional SIGIO behavior.
 *     F_GETPIPE_SZ The pipe capacity.
 *
 *     All other commands
 *              Zero.
 *
 *     On error, -1 is returned, and errno is set appropriately.
 */
#include <fcntl.h>

#ifndef F_LINUX_SPECIFIC_BASE
#define F_LINUX_SPECIFIC_BASE 1024
#endif

#ifndef F_SETPIPE_SZ
#define F_SETPIPE_SZ    (F_LINUX_SPECIFIC_BASE + 7)
#endif

#ifndef F_GETPIPE_SZ
#define F_GETPIPE_SZ    (F_LINUX_SPECIFIC_BASE + 8)
#endif

#ifndef F_DUPFD_CLOEXEC
#define F_DUPFD_CLOEXEC (F_LINUX_SPECIFIC_BASE + 6)
#endif

#ifndef F_SETOWN_EX
#define F_SETOWN_EX 15
#endif

#ifndef F_GETOWN_EX
#define F_GETOWN_EX 16
#endif

#include "trinity.h"
#include "sanitise.h"

struct syscall syscall_fcntl = {
	.name = "fcntl",
	.num_args = 3,
	.arg1name = "fd",
	.arg1type = ARG_FD,
	.arg2name = "cmd",
	.arg2type = ARG_LIST,
	.arg2list = {
		.num = 23,
		.values = { F_DUPFD, F_DUPFD_CLOEXEC, F_GETFD, F_SETFD, F_GETFL, F_SETFL, F_GETLK, F_SETLK,
		  F_SETLKW, F_GETOWN, F_SETOWN, F_GETOWN_EX, F_SETOWN_EX, F_SETPIPE_SZ, F_GETPIPE_SZ,
		  F_GETPATH, F_PREALLOCATE, F_SETSIZE, F_RDADVISE, F_RDAHEAD, F_READBOOTSTRAP, F_WRITEBOOTSTRAP,
		  F_NOCACHE, F_LOG2PHYS, F_FULLFSYNC, F_SETLKW, F_ALLOCATECONTIG, F_ALLOCATEALL, F_PEOFPOSMODE,
		  F_VOLPOSMODE},
	},
	.arg3name = "arg",
	.rettype = RET_FD,	//FIXME: Needs to mutate somehow depending on 'cmd'
};
