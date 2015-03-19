#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */

static int init_f1(void)
{
	printk(KERN_INFO "Hello world 1.\n");

	/* 
	 * A non 0 return means init_module failed; module can't be loaded. 
	 */
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

