/*
 * SYSCALL_DEFINE1(chroot, const char __user *, filename)
 *
 * On success, zero is returned.
 * On error, -1 is returned, and errno is set appropriately.
 */
#include "trinity.h"
#include "sanitise.h"

struct syscall syscall_chroot = {
	.name = "chroot",
	.num_args = 1,
	.arg1name = "filename",
	.arg1type = ARG_ADDRESS,
	.rettype = RET_ZERO_SUCCESS,
};
