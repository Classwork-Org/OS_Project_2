#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>

struct task_struct *task;
struct task_struct *out;
struct list_head *list;

int simple_init(void)
{
	printk(KERN_INFO "loading module \n");
	return 0;
}

void simple_exit(void)
{
	printk(KERN_INFO "removing module\n");
}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");