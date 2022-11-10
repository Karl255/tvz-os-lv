#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>

MODULE_DESCRIPTION("mojmodul");
MODULE_AUTHOR("ja");
MODULE_LICENSE("GPL");

void ispis(void) {
	printk(KERN_INFO "%ld %ld\n", jiffies, jiffies / HZ);
}

static int mojmodul_init(void) {
	ispis();
	return 0;
}

static void mojmodul_exit(void) {
	ispis();
}

module_init(mojmodul_init);
module_exit(mojmodul_exit);
