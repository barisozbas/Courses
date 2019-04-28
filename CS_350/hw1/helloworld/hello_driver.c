#include <linux/init.h>
#include <linux/module.h>

static int hello_init(void){
	printk(KERN_ALERT "Hello World\n");
	return 0;
}

module_init(hello_init);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("BARIS OZBAS");
