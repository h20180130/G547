#include<linux/init.h>
#include<linux/module.h>
#include<linux/version.h>
#include<linux/kernel.h>
#include<linux/types.h>
#include<linux/kdev_t.h>
#include<linux/cdev.h>
#include<linux/fs.h>
#include<linux/device.h>
#include <linux/types.h>
#include <linux/random.h>
#include <linux/uaccess.h>

uint16_t getrand(void){
    uint16_t value;
    get_random_bytes(&value, 2);
    return value;
}

static dev_t accel;

static struct cdev x_dev;
static struct cdev y_dev;
static struct cdev z_dev;
static struct class *cls;

dev_t x,y,z;
uint16_t val;

static int x_open(struct inode *i,struct file *f)
{
printk(KERN_INFO "acc_x file :open()\n");
return 0;
}
static int x_close(struct inode *i,struct file *f)
{
printk(KERN_INFO "acc_x file :close()\n");
return 0;
}
static ssize_t x_read(struct file *f,char __user *buf,size_t len,loff_t *off)
{
printk(KERN_INFO "acc_x file :read()\n");
val=getrand()&0x3ff;
copy_to_user(buf, &val, 2);
return 0;
}


static int y_open(struct inode *i,struct file *f)
{
printk(KERN_INFO "acc_y file :open()\n");
return 0;
}
static int y_close(struct inode *i,struct file *f)
{
printk(KERN_INFO "acc_y file :close()\n");
return 0;
}
static ssize_t y_read(struct file *f,char __user *buf,size_t len,loff_t *off)
{
printk(KERN_INFO "acc_y file :read()\n");
val=getrand()&0x3ff;
copy_to_user(buf, &val, 2);
return 0;
}


static int z_open(struct inode *i,struct file *f)
{
printk(KERN_INFO "acc_z file :open()\n");
return 0;
}
static int z_close(struct inode *i,struct file *f)
{
printk(KERN_INFO "acc_z file :close()\n");
return 0;
}
static ssize_t z_read(struct file *f,char __user *buf,size_t len,loff_t *off)
{
printk(KERN_INFO "acc_z file :read()\n");
val=getrand()&0x3ff;
copy_to_user(buf, &val, 2);
return 0;
}


static struct file_operations xops =
{
	.owner=THIS_MODULE,
	.open=x_open,
	.release=x_close,
	.read=x_read,
};
static struct file_operations yops =
{
	.owner=THIS_MODULE,
	.open=y_open,
	.release=y_close,
	.read=y_read,
};
static struct file_operations zops =
{
	.owner=THIS_MODULE,
	.open=z_open,
	.release=z_close,
	.read=z_read,
};



static __init int demo_init(void)
{
    printk(KERN_INFO "ADXL 345 REGISTERED\n\n");
    if((alloc_chrdev_region(&accel,0,3,"ACCELEROMETER ADXL 345"))<0)
        {
            return -1;
        }
    x=MKDEV(MAJOR(accel), MINOR(accel)+0);
    y=MKDEV(MAJOR(accel), MINOR(accel)+1);
    z=MKDEV(MAJOR(accel), MINOR(accel)+2);
    if((cls=class_create(THIS_MODULE,"chardev"))==NULL)
        {
            unregister_chrdev_region(accel,3);
            return -1;
        }
    cdev_init(&x_dev,&xops);
    device_create(cls,NULL,x,NULL,"acc_x");
    if(cdev_add(&x_dev,x,1)<0)
        {
            device_destroy(cls, x);
            class_destroy(cls);
            unregister_chrdev_region(accel, 3);
            return -1;
        }
    cdev_init(&y_dev,&yops);
    device_create(cls,NULL,y,NULL,"acc_y");
    if(cdev_add(&y_dev,y,1)<0)
        {
            cdev_del(&x_dev);
            device_destroy(cls, y);
            device_destroy(cls, x);
            class_destroy(cls);
            unregister_chrdev_region(accel, 3);
            return -1;
        }
    cdev_init(&z_dev,&zops);
    device_create(cls,NULL,z,NULL,"acc_z");
    if(cdev_add(&z_dev,z,1)<0)
        {
            cdev_del(&x_dev);
            cdev_del(&y_dev);
            device_destroy(cls, x);
            device_destroy(cls, y);
            device_destroy(cls, z);
            class_destroy(cls);
            unregister_chrdev_region(accel, 3);
            return -1;
        }
    return 0;

}


static __exit void demo_exit(void)
{
	cdev_del(&x_dev);
	cdev_del(&y_dev);
	cdev_del(&z_dev);
	device_destroy(cls,x);
	device_destroy(cls,y);
	device_destroy(cls,z);
	class_destroy(cls);
	unregister_chrdev_region(accel,3);
	printk(KERN_INFO "ADXL 345 UNREGISTERED\n\n");
	}

module_init(demo_init);
module_exit(demo_exit);

MODULE_DESCRIPTION("Device Drivers Assignment 1");
MODULE_AUTHOR("DILIP REDDY GANGULA");
MODULE_LICENSE("GPL");
    
