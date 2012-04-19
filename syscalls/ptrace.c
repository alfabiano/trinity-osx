/*
 * SYSCALL_DEFINE4(ptrace, long, request, long, pid, long, addr, long, data)
 */
#include "trinity.h"
#include "sanitise.h"
#include <stdlib.h>
#include <sys/ptrace.h>
#include <sys/types.h>

static void sanitise_ptrace(
	__unused__ unsigned long *a1,
	unsigned long *pid,
	__unused__ unsigned long *a3,
	__unused__ unsigned long *a4,
	__unused__ unsigned long *a5,
	__unused__ unsigned long *a6)
{
	unsigned int i;

	/* We must be careful to not give out ARG_PID to ptrace,
	 * because we might end up tracing the parent process, or screen/tmux,
	 * or god knows what else that we don't control, but are allowed to trace.
	 * As we can't send it a CONT, it'll just hang forever.
	 * So we just send ptrace commands to child processes.
	 * The parent will get a WIFSTOPPED, and send a CONT, and the world keeps turning.
	 *
	 * Or at least, that's the theory. In reality, this is currently causing 'no such process' errors.
	 *  but broken is at least better than hanging.
	 */
	i  = rand() % shm->running_childs;
	*pid = shm->pids[i];
}


struct syscall syscall_ptrace = {
	.name = "ptrace",
	.num_args = 4,
	.arg1name = "request",
	.arg1type = ARG_LIST,
	.arg1list = {
		.num = 23,
		.values = { PT_TRACE_ME, PT_DENY_ATTACH, PT_CONTINUE, PT_STEP, 
			    PT_KILL, PT_ATTACH, PT_DETACH }
		
	},
	.arg2name = "pid",
	.arg3name = "addr",
	.arg3type = ARG_ADDRESS,
	.arg4name = "data",
	.sanitise = sanitise_ptrace,
};
