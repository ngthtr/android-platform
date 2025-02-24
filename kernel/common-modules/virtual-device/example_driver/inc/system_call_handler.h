#ifndef SYSTEMCALLHANDLER_H
#define SYSTEMCALLHANDLER_H

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/poll.h>
#include <linux/fs.h>


int driver_open(struct inode *inode, struct file *filp);

ssize_t driver_read(struct file *filp, char __user *buf, size_t count, loff_t *offset);

ssize_t driver_write(struct file *filp, const char __user *buf, size_t count, loff_t *offset);

int driver_release(struct inode *inode, struct file *filp);

loff_t driver_llseek(struct file *filp, loff_t offset, int whence);

int driver_mmap(struct file *filp, struct vm_area_struct *vma);

long driver_ioctl(struct file *filp, unsigned int cmd, unsigned long arg);

unsigned int driver_poll(struct file *filp, poll_table *wait);

int driver_fsync(struct file *filp, loff_t start, loff_t end, int datasync);

int driver_fasync(int fd, struct file *filp, int on);

#endif