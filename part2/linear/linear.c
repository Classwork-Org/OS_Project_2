#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <linux/slab.h>

struct task_struct *task;

char* convertStateToString(long state){
	
	switch(state){
		case 0:
			return "running";
		case 1:
			return "interruptable";
		case 2:
			return "uninterruptable";
		case 4:
			return "stopped";
		case 8:
			return "traced";
		case 16:
			return "exit dead";
		case 32:
			return "exit zombie";
		case 64:
			return "dead";
		case 128:
			return "wakekill";
		case 256:
			return "waking";
		case 512:
			return "parked";
		case 1024:
			return "state_max";
		default:
			return "undefined";
	}
}

int simple_init(void)
{
	printk(KERN_INFO "starting process tree print \n");
	printk(KERN_INFO "pid: %d, parent_pid: %d, name: %s, state: %s", init_task.pid, init_task.real_parent->pid, init_task.comm, convertStateToString(init_task.state));
	for_each_process(task){
		printk(KERN_INFO "pid: %d, parent_pid: %d, name: %s, state: %s", task->pid, task->real_parent->pid, task->comm, convertStateToString(task->state));
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