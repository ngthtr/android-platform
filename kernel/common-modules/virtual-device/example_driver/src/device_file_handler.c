#include <linux/poll.h>
#include "../inc/device_file_handler.h"
#include "../inc/config.h"

int file_open_handle(struct inode *inode, struct file *filp)
{
    printk("%s: file_open_handle is called\n", TAG);
    return 0;
}

ssize_t file_read_handle(struct file *filp, char __user *buf, size_t count, loff_t *offset)
{
    const char data_from_kernel[10] = "123456789";
    ssize_t data_len = strlen(data_from_kernel) + 1;
    
    printk("%s: file_read_handle is called\n", TAG);

    if (*offset >= data_len) {
        return 0;
    }

    if (*offset + count > data_len) {
        count = data_len - *offset;
    }

    if (copy_to_user(buf, data_from_kernel + *offset, count) != 0)
    {
        printk("%s: file_read_handle copy data to user failed\n", TAG);
        return -EFAULT; 
    }

    *offset += count;
    return count;
}

ssize_t file_write_handle(struct file *filp, const char __user *buf, size_t count, loff_t *offset)
{
    printk("%s: file_write_handle is called\n", TAG);
    return count;
}

int file_release_handle(struct inode *inode, struct file *filp)
{
    printk("%s: file_release_handle is called\n", TAG);
    return 0;
}

loff_t file_llseek_handle(struct file *filp, loff_t offset, int whence)
{
    printk("%s: file_llse_handleek is called\n", TAG);
    return offset;
}

int file_mmap_handle(struct file *filp, struct vm_area_struct *vma)
{
    printk("%s: file_mmap_handle is called\n", TAG);
    return 0;
}

long file_ioctl_handle(struct file *filp, unsigned int cmd, unsigned long arg)
{
    printk("%s: file_ioct_handlel is called\n", TAG);
    return 0;
}

unsigned int file_poll_handle(struct file *filp, poll_table *wait)
{
    printk("%s: file_poll_handle is called\n", TAG);
    return 0;
}

int file_fsync_handle(struct file *filp, loff_t start, loff_t end, int datasync)
{
    printk("%s: file_fsync_handle is called\n", TAG);
    return 0;
}

int file_fasync_handle(int fd, struct file *filp, int on)
{
    printk("%s: file_fasync_handle is called\n", TAG);
    return 0;
}

