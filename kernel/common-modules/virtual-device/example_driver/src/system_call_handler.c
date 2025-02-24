// #include <Kernel/sys/_types/_ssize_t.h>

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/poll.h>
#include <linux/fs.h>
#include "../inc/system_call_handler.h"

extern int my_exported_function(int a, int b); 
int driver_open(struct inode *inode, struct file *filp)
{
    printk("driver_open is called");
    return 0;
}

ssize_t driver_read(struct file *filp, char __user *buf, size_t count, loff_t *offset)
{
    printk("driver_read is called");
    const char data_from_kernel[100] = "123456789";
    size_t retVal = copy_to_user(buf, data_from_kernel, strlen(data_from_kernel) + 1);
    if (retVal != 0)
    {
        printk("driver_read copy data to user failed");
        return 1;
    }
    
    return strlen(data_from_kernel) + 1;
}

ssize_t driver_write(struct file *filp, const char __user *buf, size_t count, loff_t *offset)
{
    int value;
    sscanf(buf, "%d", &value);

    printk("driver_write is called with data = %d", value);
    int retVal = my_exported_function(value, 10);
    printk("driver_write: number return = %d", retVal);
    return count;
}

int driver_release(struct inode *inode, struct file *filp)
{
    printk("driver_release is called");
    return 0;
}

loff_t driver_llseek(struct file *filp, loff_t offset, int whence)
{
    printk("driver_llseek is called");
    return offset;
}

int driver_mmap(struct file *filp, struct vm_area_struct *vma)
{
    printk("driver_mmap is called");
    return 0;
}

long driver_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    printk("driver_ioctl is called");
    return 0;
}

unsigned int driver_poll(struct file *filp, poll_table *wait)
{
    printk("driver_poll is called");
    return 0;
}

int driver_fsync(struct file *filp, loff_t start, loff_t end, int datasync)
{
    printk("driver_fsync is called");
    return 0;
}

int driver_fasync(int fd, struct file *filp, int on)
{
    printk("driver_fasync is called");
    return 0;
}

