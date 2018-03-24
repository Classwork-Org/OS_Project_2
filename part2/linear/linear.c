#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <linux/slab.h>

struct task_struct *task;

int simple_init(void)
{
	printk(KERN_INFO "starting process tree print \n");
	printk(KERN_INFO "pid: %d, parent_pid: %d, name: %s, state: %ld", init_task.pid, init_task.real_parent->pid, init_task.comm, init_task.state);
	for_each_process(task){
		printk(KERN_INFO "pid: %d, parent_pid: %d, name: %s, state: %ld", task->pid, task->real_parent->pid, task->comm, task->state);
	}

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