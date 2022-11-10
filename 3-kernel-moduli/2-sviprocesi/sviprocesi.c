#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/proc_fs.h>
#include <linux/ktime.h>

MODULE_DESCRIPTION("mojmodul");
MODULE_AUTHOR("ja");
MODULE_LICENSE("GPL");

void ispis(void) {
	s64 boottime_s = ktime_divns(ktime_get_boottime(), NSEC_PER_SEC);
	
	struct task_struct *process;
	
	for_each_process(process) {
		// executable name | PID | process runtime
		printk(KERN_INFO "%s\t%d\t%llus\n", process->comm, process->pid, boottime_s - (process->start_boottime) / 1000000000);
	}
	
	printk(KERN_INFO "boottime: %lld", boottime_s);
}

static int mojmodul_init(void) {
	ispis();
	return 0;
}

static void mojmodul_exit(void) {
}

module_init(mojmodul_init);
module_exit(mojmodul_exit);
