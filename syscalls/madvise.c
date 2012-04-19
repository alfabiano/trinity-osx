/*
 * SYSCALL_DEFINE3(madvise, unsigned long, start, size_t, len_in, int, behavior)
 */
#include "trinity.h"
#include "sanitise.h"

#include <sys/mman.h>

struct syscall syscall_madvise = {
	.name = "madvise",
	.num_args = 3,
	.arg1name = "start",
	.arg1type = ARG_ADDRESS,
	.arg2name = "len_in",
	.arg2type = ARG_LEN,
	.arg3name = "behaviour",
	.arg3type = ARG_LIST,
	.arg3list = {
		.num = 12,
		.values = { MADV_NORMAL, MADV_RANDOM, MADV_SEQUENTIAL, MADV_WILLNEED,
			    MADV_DONTNEED,
			    POSIX_MADV_NORMAL, MADV_SEQUENTIAL, POSIX_MADV_SEQUENTIAL, 
			    POSIX_MADV_RANDOM, POSIX_MADV_WILLNEED, POSIX_MADV_DONTNEED,
			    MADV_FREE, MADV_ZERO_WIRED_PAGES }
			    
	},
	.group = GROUP_VM,
};
