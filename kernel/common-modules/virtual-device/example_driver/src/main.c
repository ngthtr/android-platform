#include <linux/device.h>
#include "../inc/system_call_handler.h"

#define DEVICE_NAME "example_driver"
#define CLASS_NAME "example_driver"
#define TAG "example_driver"

static int major_number = -1;
static struct class*  example_class  = NULL;
static struct device* example_device = NULL;

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = driver_open,
    .read = driver_read,
    .write = driver_write,
    .release = driver_release,
    .llseek = driver_llseek, 
    .mmap = driver_mmap,
    .unlocked_ioctl = driver_ioctl,  
    .poll = driver_poll,
    .fsync = driver_fsync,
    .fasync = driver_fasync,
};

static int __init m_init(void)
{
	printk("%s: m_init is calledd\n", TAG);
    major_number = register_chrdev(0, DEVICE_NAME, &fops);
	if (major_number < 0)
	{
		printk("%s: get invalid major_number = %d\n", TAG, major_number);
		return 0;
	}
	printk("%s: get valid major_number = %d\n", TAG, major_number);

    example_class = class_create(THIS_MODULE, CLASS_NAME);
	if (example_class == NULL)
	{
		printk("example_driver: example_class is NULl");
		return 0;
	}
	printk("%s: get class successful\n", TAG);

    example_device = device_create(example_class, NULL, MKDEV(major_number, 0), NULL, DEVICE_NAME);
	if (example_device == NULL)
	{
		printk("example_driver: example_device is NULl");
	}
	printk("%s: get device successful\n", TAG);

	return 0;
}

static void __exit m_exit(void)
{
	printk("example_driver: m_exit is called\n");
	// TODO: Implement destroy pointer/class/...
}

module_init(m_init);
module_exit(m_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("truong");
MODULE_DESCRIPTION("example program");
MODULE_SOFTDEP("pre: test_driver");