#include <linux/module.h>
#include <linux/timer.h>
#include <linux/sched/loadavg.h>
#include <linux/printk.h>
#include <linux/jiffies.h>
#include <linux/kernel.h>

static struct timer_list cpu_timer;
static unsigned int interval = 10;

module_param(interval, uint, 0644);

void log_load(struct timer_list *t){
    unsigned long load = (unsigned long)(avenrun[0]/65536 * 100);

    pr_info("CPU LOAD: %lu%%\n", load);

    mod_timer(&cpu_timer, jiffies + msecs_to_jiffies(interval * 1000));
}

int init_module(void){
    pr_info("CPU load logger init\n");

    timer_setup(&cpu_timer, log_load, 0);
    mod_timer(&cpu_timer, jiffies + msecs_to_jiffies(interval * 1000));

    return 0;
}

void cleanup_module(void){
    pr_info("CPU load logger cleanup\n");

    del_timer(&cpu_timer);

}

MODULE_LICENSE("GPL");