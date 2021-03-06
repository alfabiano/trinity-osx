/*
 * SYSCALL_DEFINE2(lstat, const char __user *, filename,
                   struct __old_kernel_stat __user *, statbuf)
 */
#include "trinity.h"
#include "sanitise.h"

struct syscall syscall_lstat = {
	.name = "lstat",
	.num_args = 2,
	.arg1name = "filename",
	.arg2name = "statbuf",
	.arg2type = ARG_ADDRESS,
};
