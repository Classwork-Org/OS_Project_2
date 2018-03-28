#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/slab.h>

struct task_struct *task;
struct task_struct *out;
struct list_head *list;

char* convertStateToString(long state){
	
	int i = 0;
	long temp = 0;
	char* result;

	if(state == 0){
		return "running";
	}
	else{
		result = (char*)kmalloc(sizeof(char)*250, GFP_KERNEL);
	}

	strcpy(result, "");
	for(i = 0; i<=10; i++){
		temp = state & (1<<i);
		switch(temp){
			case 1:
				strcat(result,  "interruptable ");
				break;
			case 2:
				strcat(result,  "uninterruptable ");
				break;
			case 4:
				strcat(result,  "stopped ");
				break;
			case 8:
				strcat(result,  "traced ");
				break;
			case 16:
				strcat(result,  "exit dead ");
				break;
			case 32:
				strcat(result,  "exit zombie ");
				break;
			case 64:
				strcat(result,  "dead ");
				break;
			case 128:
				strcat(result,  "wakekill ");
				break;
			case 256:
				strcat(result,  "waking ");
				break;
			case 512:
				strcat(result,  "parked ");
				break;
			case 1024:
				strcat(result,  "state_max ");
				break;
			default:
				strcat(result,  "");
				break;
		}
	}
	return result;
}

void dfs_process_tree(struct task_struct *next)
{
	struct task_struct *child;
	struct list_head *ptr;
	printk(KERN_INFO "pid: %d, parent_pid: %d, name: %s, state: %s, state(num): %ld", \
	 next->pid, next->real_parent->pid, next->comm, convertStateToString(next->state),\
	 next->state);
	list_for_each(ptr, &next->children){
		child = list_entry(ptr, struct task_struct, sibling);
		dfs_process_tree(child);
	}
}

int simple_init(void)
{
	printk(KERN_INFO "starting process tree print\n");
	dfs_process_tree(&init_task);
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