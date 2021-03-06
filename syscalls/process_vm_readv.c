/*
 * SYSCALL_DEFINE6(process_vm_readv, pid_t, pid, const struct iovec __user *, lvec,
 *                unsigned long, liovcnt, const struct iovec __user *, rvec,
 *                unsigned long, riovcnt, unsigned long, flags)
 */

#include "trinity.h"
#include "sanitise.h"

struct syscall syscall_process_vm_readv = {
	.name = "process_vm_readv",
	.num_args = 6,
	.arg1name = "pid",
	.arg1type = ARG_PID,
	.arg2name = "lvec",
	.arg2type = ARG_ADDRESS,
	.arg3name = "liovcnt",
	.arg3type = ARG_LEN,
	.arg4name = "rvec",
	.arg4type = ARG_LEN,
	.arg5name = "riovcnt",
	.arg5type = ARG_ADDRESS,
	.arg6name = "flags",
	.arg6type = ARG_LIST,
	.arg6list = {
		.num = 1,
		.values = { 0 },
	},
};
