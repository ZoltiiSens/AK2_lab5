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

static LIST_HEAD(l_struct_list);

void print_hello(unsigned int counter_h1)
{

	int i;

	for (i = 0; i < counter_h1; i++) {
		struct l_struct *l_struct_ex = kmalloc(sizeof(*l_struct_ex), GFP_KERNEL);

		if (i == 4)
			l_struct_ex = 0;
		l_struct_ex->timestamp_start = ktime_get();
		pr_info("Hello, world!\n");
		l_struct_ex->timestamp_end = ktime_get();
		list_add(&l_struct_ex->list, &l_struct_list);
	}
}
EXPORT_SYMBOL(print_hello);

static void __exit hello1_exit(void)
{
	struct l_struct *l_struct_ex, *temp;

	list_for_each_entry_safe(l_struct_ex, temp, &l_struct_list, list) {
		pr_info("Time stamp: %lld\n", l_struct_ex->timestamp_start);
		pr_info("Time spent: %lld\n", ktime_to_ns(ktime_sub(l_struct_ex->timestamp_end, l_struct_ex->timestamp_start)));
		list_del(&l_struct_ex->list);
		kfree(l_struct_ex);
	}
}


module_exit(hello1_exit);
