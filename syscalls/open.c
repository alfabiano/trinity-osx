/*
 * SYSCALL_DEFINE3(open, const char __user *, filename, int, flags, int, mode)
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "trinity.h"
#include "sanitise.h"

#ifndef O_PATH
#define O_PATH        010000000 /* Resolve pathname but do not open file.  */
#endif

struct syscall syscall_open = {
	.name = "open",
	.num_args = 3,
	.arg1name = "filename",
	.arg1type = ARG_ADDRESS,
	.arg2name = "flags",
	.arg2type = ARG_LIST,
	.arg2list = {
		.num = 19,
		.values = { O_RDONLY, O_WRONLY, O_RDWR, O_CREAT, O_EXCL, O_NOCTTY,
			    O_TRUNC, O_APPEND, O_NONBLOCK, O_SYNC, O_ASYNC,
			    O_DIRECTORY, O_NOFOLLOW, O_PATH, O_DSYNC,
			    O_SHLOCK, O_EXLOCK, O_SYMLINK, O_EVTONLY },
	},
	.arg3name = "mode",
};
