/*
 * SYSCALL_DEFINE3(rt_sigqueueinfo, pid_t, pid, int, sig, siginfo_t __user *, uinfo)
 */
#include "trinity.h"
#include "sanitise.h"

struct syscall syscall_rt_sigqueueinfo = {
	.name = "rt_sigqueueinfo",
	.num_args = 3,
	.arg1name = "pid",
	.arg1type = ARG_PID,
	.arg2name = "sig",
	.arg3name = "uinfo",
	.arg3type = ARG_ADDRESS,
};
