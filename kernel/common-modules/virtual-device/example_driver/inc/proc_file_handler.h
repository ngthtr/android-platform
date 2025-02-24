#pragma once
#include <linux/proc_fs.h>
#include <linux/fs.h>  
int proc_open_handle(struct inode *inode, struct file *file);

ssize_t proc_read_handle(struct file *file, char __user *buf, size_t count, loff_t *pos);

ssize_t proc_read_iter_handle(struct kiocb *kiocb, struct iov_iter *iter);

ssize_t proc_write_handle(struct file *file, const char __user *buf, size_t count, loff_t *pos);

loff_t proc_lseek_handle(struct file *file, loff_t offset, int whence);

int proc_release_handle(struct inode *inode, struct file *file);

__poll_t proc_poll_handle(struct file *file, struct poll_table_struct *wait);

long proc_ioctl_handle(struct file *file, unsigned int cmd, unsigned long arg);

long proc_compat_ioctl_handle(struct file *file, unsigned int cmd, unsigned long arg);

int proc_mmap_handle(struct file *file, struct vm_area_struct *vma);
