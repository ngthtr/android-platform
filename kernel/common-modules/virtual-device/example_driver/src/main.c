#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/device.h>
#include "../inc/device_file_handler.h"
#include "../inc/proc_file_handler.h"
#include "../inc/config.h"


static int major_number = -1;
static struct class*  example_class = NULL;
static struct device* example_device = NULL;
static struct proc_dir_entry *proc_entry = NULL;

static struct file_operations f_ops = {
    .owner = THIS_MODULE,
    .open = file_open_handle,
    .read = file_read_handle,
    .write = file_write_handle,
    .release = file_release_handle,
    .llseek = file_llseek_handle, 
    .mmap = file_mmap_handle,
    .unlocked_ioctl = file_ioctl_handle,  
    .poll = file_poll_handle,
    .fsync = file_fsync_handle,
    .fasync = file_fasync_handle,
};

static struct proc_ops p_ops = {
	.proc_open = proc_open_handle,
	.proc_read = proc_read_handle,
	.proc_read_iter = proc_read_iter_handle,
	.proc_write = proc_write_handle,
	.proc_lseek = proc_lseek_handle,
	.proc_release = proc_release_handle,
	.proc_poll = proc_poll_handle,
	.proc_ioctl = proc_ioctl_handle,
	.proc_mmap = proc_mmap_handle,
};

static int init_device_file(struct file_operations *f_ops)
{
	printk("%s: init_device_file is called\n", TAG);

	major_number = register_chrdev(0, DEVICE_NAME, f_ops);
	if (major_number < 0)
	{
		printk("%s: get invalid major_number = %d\n", TAG, major_number);
		return ERROR_STATUS;
	}
	printk("%s: get valid major_number = %d\n", TAG, major_number);

    example_class = class_create(CLASS_NAME);
	if (example_class == NULL)
	{
		unregister_chrdev_region(major_number, 1);
		printk("example_driver: example_class is NULl");
		return ERROR_STATUS;
	}
	printk("%s: get class successful\n", TAG);

    example_device = device_create(example_class, NULL, MKDEV(major_number, 0), NULL, DEVICE_NAME);
	if (example_device == NULL)
	{
		class_destroy(example_class);
        unregister_chrdev_region(major_number, 1);
		printk("example_driver: example_device is NULl");
		return ERROR_STATUS;
	}

	printk("%s: init_device_file successful\n", TAG);
	return SUCCESS_STATUS;
}

static int init_proc_file(struct proc_ops *p_ops)
{
	printk("%s: init_proc_file is called\n", TAG);

	proc_entry = proc_create(PROC_NAME, 0, NULL, p_ops);
	if (!proc_entry) {
		printk("%s: create proc file failed\n", TAG);
        return ERROR_STATUS;
    }

	printk("%s: init_proc_file successful\n", TAG);
	return SUCCESS_STATUS;
}

static int release_device_file(void)
{
	printk("%s: release_device_file is called\n", TAG);
	device_destroy(example_class, MKDEV(major_number, 0));
    class_destroy(example_class);
    unregister_chrdev_region(major_number, 1);
	return SUCCESS_STATUS;
}

static int release_proc_file(void)
{
	printk("%s: release_proc_file is called\n", TAG);
	remove_proc_entry(PROC_NAME, NULL);
	return SUCCESS_STATUS;
}

static int __init m_init(void)
{
	printk("%s: m_init is called\n", TAG);

    if (init_device_file(&f_ops) == ERROR_STATUS)
	{
		printk("%s: initialize device file failed\n", TAG);
	}

	if (init_proc_file(&p_ops) == ERROR_STATUS)
	{
		printk("%s: initialize proc file failed\n", TAG);
	}

	return 0;
}

static void __exit m_exit(void)
{
	printk("%s: m_exit is called\n", TAG);

	release_device_file();
	release_proc_file();
}

module_init(m_init);
module_exit(m_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("truong");
MODULE_DESCRIPTION("example program");