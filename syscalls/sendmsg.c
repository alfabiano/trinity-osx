/*
 * SYSCALL_DEFINE3(sendmsg, int, fd, struct msghdr __user *, msg, unsigned, flags)
 */

#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "trinity.h"
#include "sanitise.h"

#define MSG_CMSG_COMPAT 0x80000000      /* This message needs 32 bit fixups */

static void sanitise_sendmsg(
	__unused__ unsigned long *fd,
	unsigned long *a2,
	__unused__ unsigned long *a3,
	__unused__ unsigned long *a4,
	__unused__ unsigned long *a5,
	__unused__ unsigned long *a6)
{
	struct msghdr *msg;

        msg = malloc(sizeof(struct msghdr));
	if (msg == NULL) {
		*a2 = (unsigned long) get_address();
		return;
	}

	msg->msg_name = get_address();
	msg->msg_namelen = get_len();
	msg->msg_iov = get_address();
	msg->msg_iovlen = get_len();
	msg->msg_control = get_address();
	msg->msg_controllen = get_len();
	msg->msg_flags = rand();

	*a2 = (unsigned long) msg;
}

struct syscall syscall_sendmsg = {
	.name = "sendmsg",
	.num_args = 3,
	.arg1name = "fd",
	.arg1type = ARG_FD,
	.arg2name = "msg",
	.arg3name = "flags",
	.arg3type = ARG_LIST,
	.arg3list = {
		.num = 19,
		.values = { MSG_OOB, MSG_PEEK, MSG_DONTROUTE, MSG_CTRUNC,
			    MSG_TRUNC, MSG_DONTWAIT, MSG_EOR,
			    MSG_WAITALL, MSG_CMSG_COMPAT 
			},
	},
	.sanitise = sanitise_sendmsg,
};
