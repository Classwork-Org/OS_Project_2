#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>

struct task_struct *task;
struct task_struct *out;
struct list_head *list;

void dfs_process_tree(struct task_struct *next)
{
	struct task_struct *child;
	struct list_head *ptr;
	printk(KERN_INFO "pid: %d, parent_pid: %d, name: %s, state: %ld", next->pid, next->real_parent->pid, next->comm, next->state);
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
	printk(KERN_INFO "removing module and saving output to output.txt\n");
}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");