#include <linux/device.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

int my_exported_function(int a, int b) {
    printk("my_exported_function() is called");
    return 1;
}
EXPORT_SYMBOL(my_exported_function); 

static int __init m_init(void)
{
	return 0;
}

static void __exit m_exit(void)
{
}

module_init(m_init);
module_exit(m_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("truong");
MODULE_DESCRIPTION("test program");
