#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>

#include <linux/errno.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/ktime.h>
#include "hello1.h"

MODULE_AUTHOR("Roman Lytvynenko <lytvynenko.roman@lll.kpi.ua>");
MODULE_DESCRIPTION("Hello, world! module1");
MODULE_LICENSE("Dual BSD/GPL");

static unsigned int counter = 1;
module_param(counter, uint, 0644);
MODULE_PARM_DESC(counter, "How many times print 'Hello, world!'");

static int __init hello2_init(void)
{
//	if (counter > 10) {
//		pr_err("Parameter is too large, make it <= 10\n");
//		return -EINVAL;
//	}
	BUG_ON(counter > 10);

	if (counter == 0 || (counter >= 5 && counter <= 10))
		pr_warn("Parameter has a non-standard value. Continuing...\n");

	print_hello(counter);

	return 0;
}

static void __exit hello2_exit(void)
{
	pr_info("Hello2 module uninstalled\n");
}

module_init(hello2_init);
module_exit(hello2_exit);
