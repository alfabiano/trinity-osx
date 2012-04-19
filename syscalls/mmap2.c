/*
 * sys_mmap2 (unsigned long addr, unsigned long len, int prot, int flags, int fd, long pgoff)
 */
#include <sys/mman.h>

#include "trinity.h"
#include "sanitise.h"

#ifndef MAP_UNINITIALIZED
#define MAP_UNINITIALIZED 0x4000000
#endif

struct syscall syscall_mmap2 = {
	.name = "mmap2",
	.num_args = 6,
	.sanitise = sanitise_mmap,
	.arg1name = "addr",
	.arg1type = ARG_ADDRESS,
	.arg2name = "len",
	.arg2type = ARG_LEN,
	.arg3name = "prot",
	.arg3type = ARG_LIST,
	.arg3list = {
		.num = 4,
		.values = { PROT_READ, PROT_WRITE, PROT_EXEC },
	},
	.arg4name = "flags",
	.arg4type = ARG_LIST,
	.arg4list = {
		.num = 14,
                .values = { MAP_SHARED, MAP_PRIVATE, MAP_FIXED, MAP_NORESERVE,
                            MAP_UNINITIALIZED,
                            MAP_ANON, MAP_FILE, MAP_HASSEMAPHORE, MAP_NOCACHE },
	},
	.arg5name = "fd",
	.arg5type = ARG_FD,
	.arg6name = "pgoff",
	.group = GROUP_VM,
};
