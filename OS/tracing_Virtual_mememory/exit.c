#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
static void exit_f1(void)
{
	printk(KERN_INFO "Goodbye world 1.\n");
}




module_exit(exit_f1);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("ranjan/tanmoy");

