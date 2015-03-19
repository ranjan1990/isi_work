#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include<linux/sched.h>


void trace_mem(struct task_struct *t){
	struct   mm_struct *trace_mm;
	trace_mm=t->mm;
	if(trace_mm!=NULL){
		printk("start-code end-code start-data end-data start-stack\n");
		printk("%lu %lu %lu %lu %lu\n",trace_mm->start_code,trace_mm->end_code,trace_mm->start_data,trace_mm->end_data,trace_mm->start_stack);
	}


}

void trace_process(void){
	struct task_struct *trace_task;
	printk(KERN_INFO"printing all pid\n");
	

	for(trace_task=&init_task;(trace_task=next_task(trace_task))!= &init_task;){
		printk("pid =%d state%ld name=%s uid=%d\n",trace_task->pid,trace_task->state,trace_task->comm,trace_task->loginuid);
		trace_mem(trace_task);

	}

}
static int init_f1(void)
{
	printk(KERN_INFO "kernel module loaded\n");

	trace_process();



	return 0;
}

static void exit_f1(void)
{
	printk(KERN_INFO "Goodbye world 1.\n");
}




module_init(init_f1);
module_exit(exit_f1);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("ranjan/tanmoy");

