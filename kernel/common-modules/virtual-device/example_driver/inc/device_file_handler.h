#pragma once
#include <linux/poll.h>
#include <linux/fs.h>

int file_open_handle(struct inode *inode, struct file *filp);

ssize_t file_read_handle(struct file *filp, char __user *buf, size_t count, loff_t *offset);

ssize_t file_write_handle(struct file *filp, const char __user *buf, size_t count, loff_t *offset);

int file_release_handle(struct inode *inode, struct file *filp);

loff_t file_llseek_handle(struct file *filp, loff_t offset, int whence);

int file_mmap_handle(struct file *filp, struct vm_area_struct *vma);

long file_ioctl_handle(struct file *filp, unsigned int cmd, unsigned long arg);

unsigned int file_poll_handle(struct file *filp, poll_table *wait);

int file_fsync_handle(struct file *filp, loff_t start, loff_t end, int datasync);

int file_fasync_handle(int fd, struct file *filp, int on);
