/*
 * SYSCALL_DEFINE3(ioctl, unsigned int, fd, unsigned int, cmd, unsigned long, arg)
 */
#include <stdlib.h>
#include <sys/ioctl.h>
//#include <sys/major.h>

#include "trinity.h"
#include "sanitise.h"

/*
#include <linux/agpgart.h>
#include <linux/atmioc.h>
#include <linux/cciss_ioctl.h>
#include <linux/cm4000_cs.h>
#include <linux/dm-ioctl.h>
#include <linux/dn.h>
#include <linux/gigaset_dev.h>
#include <linux/i2o-dev.h>
#include <linux/ipmi.h>
#include <linux/kvm.h>
#include <linux/mmtimer.h>
#include <linux/phantom.h>
#include <linux/pktcdvd.h>
#include <linux/ppdev.h>
#include <linux/rfkill.h>
#include <linux/spi/spidev.h>
#include <linux/sonet.h>
#include <linux/suspend_ioctls.h>
#include <linux/synclink.h>
#include <linux/usb/tmc.h>
#include <linux/uinput.h>
#include <linux/vhost.h>
#include <linux/videodev2.h>
#include <linux/watchdog.h>
#include <mtd/ubi-user.h>
#include <rdma/ib_user_mad.h>
*/
// msm_mdp.h not exported to glibc yet.
#define MSMFB_IOCTL_MAGIC 'm'

struct ioctl {
	char *name;
	unsigned int request;
	void (*sanitise)(
		unsigned long *, unsigned long *, unsigned long *,
		unsigned long *, unsigned long *, unsigned long *);
};

struct ioctl ioctllist[] = {
#include "ioctls/scsi-generic.h"
/*
#include "ioctls/framebuffer.h"
#include "ioctls/console.h"
#include "ioctls/cdrom.h"
#include "ioctls/scsi.h"
#include "ioctls/tty.h"
#include "ioctls/vt.h"
#include "ioctls/socket.h"
#include "ioctls/snd.h"
#include "ioctls/mem.h"
#include "ioctls/sisfb.h"
*/
};

#define NR_IOCTLS sizeof(ioctllist)/sizeof(struct ioctl)

static void generic_sanitise_ioctl(
		__unused__ unsigned long *fd,
		unsigned long *cmd,
		unsigned long *arg,
		__unused__ unsigned long *a4,
		__unused__ unsigned long *a5,
		__unused__ unsigned long *a6)
{
	unsigned int i, j;
	unsigned int nr_elements;
	unsigned int *ptr;
	void *addr;

	/* One time in 50, mangle it. */
	if ((rand() % 50)==0) {

		/* mangle the cmd by ORing up to 4 random bits */
		for (i=0; i < (unsigned int)(rand() % 4); i++)
			*cmd |= 1L << (rand() % 32);

		/* mangle the cmd by ANDing up to 4 random bits */
		for (i=0; i < (unsigned int)(rand() % 4); i++)
			*cmd &= 1L << (rand() % 32);
	}

	/* the argument could mean anything, because ioctl sucks like that. */
	switch (rand() % 10) {
	case 0:	*arg = get_interesting_32bit_value();
		break;
	case 1 ... 5:
		*arg = (unsigned long)page_rand;
		break;
	case 6 ... 9:
		*arg = (unsigned long)page_rand;
		ptr = (unsigned int*)page_rand;
		/* manufacture a random struct */

		nr_elements = rand() % 10;
		for (i=0; i<nr_elements; i++) {
			j = rand() % 2;

			switch (j) {
			case 0: *ptr = get_interesting_32bit_value();
				ptr+= sizeof(unsigned int);
				break;
			case 1:	addr = get_address();
				*ptr = (unsigned long) (addr);
				ptr+= sizeof(unsigned long);
				break;
			}
		}
		break;
	}
}

static void sanitise_ioctl(
		__unused__ unsigned long *fd,
		unsigned long *cmd,
		unsigned long *arg,
		__unused__ unsigned long *a4,
		__unused__ unsigned long *a5,
		__unused__ unsigned long *a6)
{
	int ioctlnr;

	ioctlnr = rand() % NR_IOCTLS;
	*cmd = ioctllist[ioctlnr].request;

	if (ioctllist[ioctlnr].sanitise)
		ioctllist[ioctlnr].sanitise(fd, cmd, arg, a4, a5, a6);
	else
		generic_sanitise_ioctl(fd, cmd, arg, a4, a5, a6);
}

struct syscall syscall_ioctl = {
	.name = "ioctl",
	.num_args = 3,
	.arg1name = "fd",
	.arg1type = ARG_FD,
	.arg2name = "cmd",
	.arg3name = "arg",
	.arg3type = ARG_RANDPAGE,
	.sanitise = sanitise_ioctl,
};
