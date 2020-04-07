#include <linux/module.h>
#include <linux/netlink.h>
#include <net/sock.h>
#include <linux/string.h>
#include <inttypes.h>

#define NETLINK_TEST_PROTOCOL 31

static struct sock *nl_sk = NULL;

static void nlmsg_dump(struct nlmsghdr *nlh)
{

	printk("nlmsg_type: %PRId32\n", nlh->nlmsg_type);
	printk("nlmsg_flags: %PRId32\n", nlh->nlmsg_flags);
	printk("nlmsg_seq: %PRId32\n", nlh->nlmsg_seq);
	printk("nlmsg_pid: %PRId32\n", nlh->nlmsg_pid);
}

static void netlink_recv_msg_fn(struct sk_buff *skb_in)
{
	
}

static struct netlink_kernel_cfg cfg = {
	.input = netlink_recv_msg_fn,
};


static int __init NetlinkGreetings_init(void)
{
	printk(KERN_INFO "Hello kernel, greetings inserted\n");
	nl_sk = netlink_kernel_create(&init_net, NETLINK_TEST_PROTOCOL, &cfg);
	
	if(!nl_sk){
		printk(KERN_INFO "Kernel netlink protocol %u socket creation failed.\n",NETLINK_TEST_PROTOCOL);
		return -ENOMEM;
	}
	printk(KERN_INFO "Netlink socket created succesfully");

	return 0;
}

static void __exit NetlinkGreetings_exit(void)
{
	printk(KERN_INFO "Byebye Exiting greetings \n");
	netlink_kernel_release(nl_sk);
	nl_sk = NULL;
}
module_init(NetlinkGreetings_init);
module_exit(NetlinkGreetings_exit);

MODULE_LICENSE("GPL");


