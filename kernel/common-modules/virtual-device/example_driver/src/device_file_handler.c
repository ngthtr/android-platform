#include <linux/poll.h>
#include "../inc/device_file_handler.h"
#include "../inc/signal_handler.h"
#include "../inc/config.h"

extern int send_msg(int signal, int data);
const unsigned int CMD_PID = 123;
static struct task_struct *task;

int file_open_handle(struct inode *inode, struct file *filp)
{
    printk("%s: file_open_handle is called\n", TAG);
    return 0;
}

ssize_t file_read_handle(struct file *filp, char __user *buf, size_t count, loff_t *offset)
{
    return count;
}

ssize_t file_write_handle(struct file *filp, const char __user *buf, size_t count, loff_t *offset)
{
    printk("%s: file_write_handle is called\n", TAG);

    // Read and get data
    const int SIZE_BUFFER = 255;
    char buffer[SIZE_BUFFER];
    int bytes_writen = count > SIZE_BUFFER ? SIZE_BUFFER : count;

    if (copy_from_user(buffer, buf, bytes_writen))
    {
        return -EFAULT;
    }
    printk("%s: string command = %s\n", TAG, buffer);

    // Send message by using signal
    if (send_msg(buffer) != SUCCESS_STATUS)
    {
        printk("%s: send message has error", TAG);
        return -EFAULT;
    }

    // Send message by using netlink socket
    

    return bytes_writen;
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
    if (cmd == CMD_PID)
    {
        extern int app_pid;
        extern struct task_struct* task;

        app_pid = (int) arg;
        task = pid_task(find_get_pid(app_pid), PIDTYPE_PID);

		printk("%s: Userspace app with PID %ld is registered\n", TAG, arg);
    }
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

