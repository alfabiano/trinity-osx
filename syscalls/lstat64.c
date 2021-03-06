/*
 * SYSCALL_DEFINE2(lstat64, const char __user *, filename,
                 struct stat64 __user *, statbuf)
 */
#include "trinity.h"
#include "sanitise.h"

struct syscall syscall_lstat64 = {
	.name = "lstat64",
	.num_args = 2,
	.arg1name = "filename",
	.arg2name = "statbuf",
	.arg2type = ARG_ADDRESS,
};
