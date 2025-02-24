#include <linux/kernel.h>
#include <linux/module.h>
#include "../inc/proc_file_handler.h"
#include "../inc/config.h"

int proc_open_handle(struct inode *inode, struct file *file)
{
    printk("%s: proc_open_handle is called\n", TAG);
    return 0;
}

ssize_t proc_read_handle(struct file *file, char __user *buf, size_t count, loff_t *pos)
{
    printk("%s: proc_read_handle is called\n", TAG);
    return count;
}

ssize_t proc_read_iter_handle(struct kiocb *kiocb, struct iov_iter *iter)
{
    printk("%s: proc_read_iter_handle is called\n", TAG);
    return 0;
}

ssize_t proc_write_handle(struct file *file, const char __user *buf, size_t count, loff_t *pos)
{
    printk("%s: proc_read_iter_handle is called\n", TAG);
    return 0;
}

loff_t proc_lseek_handle(struct file *file, loff_t offset, int whence)
{
    printk("%s: proc_lseek_handle is called\n", TAG);
    return offset;
}

int proc_release_handle(struct inode *inode, struct file *file)
{
    printk("%s: proc_release_handle is called\n", TAG);
    return 0;
}

__poll_t proc_poll_handle(struct file *file, struct poll_table_struct *wait)
{
    printk("%s: proc_poll_handle is called\n", TAG);
    return 0;
}

long proc_ioctl_handle(struct file *file, unsigned int cmd, unsigned long arg)
{
    printk("%s: proc_ioctl_handle is called\n", TAG);
    return 0;
}

long proc_compat_ioctl_handle(struct file *file, unsigned int cmd, unsigned long arg)
{
    printk("%s: proc_compat_ioctl_handle is called\n", TAG);
    return 0;
}

int proc_mmap_handle(struct file *file, struct vm_area_struct *vma)
{
    printk("%s: proc_mmap_handle is called\n", TAG);
    return 0;
}
