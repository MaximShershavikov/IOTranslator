/**********************************************************************************

    IOTranslator version 1.0. Modul of IOTranslator v1.0
    Copyright (C) 2019  Maxim Shershavikov

    This file is part of IOTranslator v1.0.

    IOTranslator v1.0 is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    IOTranslator v1.0 is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

    Email m.shershavikov@yandex.ru

**********************************************************************************/

#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/uaccess.h>

#define MODULNAME "ModulDevIOTranslator"
#define DEVNAME   "VirtualDevIOTranslator"

#define IDENTIFI  0x1AF652D8
#define WRITEPORT 0x10FFE701
#define READPORT  0x20AA3302

#define DEVCOUNT 1
#define DEVFIRST 0
#define ZERO     0

static dev_t Dev_t;
static int Major = 0;
static int Minor = 0;
static int ProcNumber = 0;
static char rw = 0;
static struct cdev *Cdev;
static struct class *DevClass;

struct InOut_Operations
{
	unsigned int Identifi;
	unsigned short PortAddr;
	unsigned int WriteToPort;
	unsigned int ReadFromPort;
	unsigned int Mode;
};

static int OpenDevIOTranslator(struct inode *inode, struct file *file);
static int CloseDevIOTranslator(struct inode *inode, struct file *file);
static ssize_t ReadFromDevIOTranslator(struct file *file, char __user *buf, size_t sizebuf, loff_t *ptr);
static ssize_t WriteToDevIOTranslator(struct file *file, const char __user *buf, size_t sizebuf, loff_t *ptr);

static const struct file_operations FileOperations = {
	.owner = THIS_MODULE,
	.open = OpenDevIOTranslator,
	.release = CloseDevIOTranslator,
	.read = ReadFromDevIOTranslator,
	.write = WriteToDevIOTranslator,
};

static int __init IOTranslator_Init(void);
static void __exit IOTranslator_Exit(void);

module_init(IOTranslator_Init);
module_exit(IOTranslator_Exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Maxim Shershavikov");
MODULE_VERSION("1.0");


