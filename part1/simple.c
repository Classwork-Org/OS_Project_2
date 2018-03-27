#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <linux/slab.h>

struct birthday
{
	int day;
	int month;
	int year;
	struct list_head list;
};

struct birthday birthdayList;

int simple_init(void)
{
	printk(KERN_INFO "loading module \n");

	struct birthday* person;
	INIT_LIST_HEAD(&birthdayList.list);

	//add five
	int i;
	for(i = 0; i<5; i++)
	{
		person = kmalloc(sizeof(*person), GFP_KERNEL);
		person->day = i+1;
		person->month = i+1;
		person->year = 1900;

		list_add_tail(&(person->list), &birthdayList.list);
	}

	//print five
	struct list_head *ptr;
	list_for_each(ptr, &birthdayList.list){
		printk(KERN_INFO "added day %d", list_entry(ptr, struct birthday, list)->day);
	}

	return 0;
}

void simple_exit(void)
{
	struct birthday *ptr,*next;

	//remove everything
	printk(KERN_INFO "removing module\n");
	list_for_each_entry_safe(ptr,next,&birthdayList.list,list){
		printk(KERN_INFO "removing birthday %d\n", ptr->day);
		list_del(&ptr->list);
		kfree(ptr);
	}
}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");