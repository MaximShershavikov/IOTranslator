/**********************************************************************************

    IOTranslator version 1.0. Modul of IOTranslator v1.0 Executes assembler commands in, out
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

#include "ModulIOTranslator.h"

static int OpenDevIOTranslator(struct inode *inode, struct file *file)
{
	struct InOut_Operations *OpIoStruct;

	OpIoStruct = (struct InOut_Operations*)kmalloc(sizeof(struct InOut_Operations), GFP_KERNEL);
	file->private_data = OpIoStruct;

	OpIoStruct->Identifi 	 = ZERO;
	OpIoStruct->PortAddr 	 = ZERO;
	OpIoStruct->WriteToPort  = ZERO;
	OpIoStruct->ReadFromPort = ZERO;
	OpIoStruct->Mode 	 = ZERO;

	ProcNumber++;
	printk
	(
		KERN_INFO 
		"\nIOTranslator v1.0: The process opened the virtual device.\n" 
                "IOTranslator v1.0: The number of processes using the virtual device %d\n", 	
		ProcNumber
	);
	return 0;
}

static int CloseDevIOTranslator(struct inode *inode, struct file *file)
{
	struct InOut_Operations *OpIoStruct;

	OpIoStruct = file->private_data;
	if (OpIoStruct) kfree(OpIoStruct);
	OpIoStruct = NULL;
	file->private_data = NULL;

	ProcNumber--;
	printk
	(
		KERN_INFO 
		"\nIOTranslator v1.0: The process closed the virtual device.\n"
                "IOTranslator v1.0: The number of processes using the virtual device %d\n", 			
		ProcNumber
	);
	return 0;
}

static ssize_t ReadFromDevIOTranslator(struct file *file, char __user *buf, size_t sizebuf, loff_t *ptr)
{
	struct InOut_Operations *OpIoStruct;
	OpIoStruct = file->private_data;

	if (rw == 'r')
	{
		copy_to_user(buf, OpIoStruct, sizebuf);
		printk(KERN_INFO "\nIOTranslator v1.0: ReadFromDevIOTranslator function is" 
				 " complete with data reading [%c]\n", rw);
		rw = ZERO;
		return sizebuf;
	}
	else 
	{
		printk(KERN_INFO "\nIOTranslator v1.0: ReadFromDevIOTranslator function is"
				 " complete without data reading\n");
		return 0;
	}
}

static ssize_t WriteToDevIOTranslator(struct file *file, const char __user *buf, size_t sizebuf, loff_t *ptr)
{
	struct InOut_Operations *OpIoStruct;

	OpIoStruct = file->private_data;
	copy_from_user(OpIoStruct, buf, sizebuf);

	if (OpIoStruct->Identifi == IDENTIFI)
	{
		switch (OpIoStruct->Mode)
		{
		case WRITEPORT:
			asm volatile
			(
				"movl $0, %edx\n\t"
				"movl $0, %eax\n\t" 
			);
			asm volatile
			(
				"mov %%eax, %0\n\t"
				"mov %%dx, %1\n\t"
				"out %%eax, %%dx\n\t"
				: : "r" (OpIoStruct->WriteToPort),
				"r" (OpIoStruct->PortAddr)

			);
			rw = 'w';
			printk
			(
				KERN_INFO 
				"\nIOTranslator v1.0: out dx, eax\n"
				"IOTranslator v1.0: eax [Data to Port] = 0x%x\n"
 				"IOTranslator v1.0: dx [Addr Port] = 0x%x\n"
				"IOTranslator v1.0: [%c]\n",
				OpIoStruct->WriteToPort, OpIoStruct->PortAddr, rw
			);
			break;
		case READPORT:
			asm volatile
			(
				"movl $0, %eax\n\t"
				"movl $0, %edx\n\t"
			);	
			asm volatile
			(
				"mov %%ax, %1\n\t"
				"mov %%ax, %%dx\n\t"
				"movl $0, %%eax\n\t"
				"in %%dx, %%eax\n\t"
				"nop\n\t" "nop\n\t"
				"nop\n\t" "nop\n\t"
				"nop\n\t" "nop\n\t"
				"nop\n\t" "nop\n\t"
				"nop\n\t" "nop\n\t"
				"nop\n\t" "nop\n\t"
				"nop\n\t" "nop\n\t"
				"nop\n\t" "nop\n\t"
				"nop\n\t" "nop\n\t"
				"nop\n\t" "nop\n\t"
				"nop\n\t" "nop\n\t"
				"nop\n\t" "nop\n\t"
				"nop\n\t" "nop\n\t"
				"nop\n\t" "nop\n\t"
				"nop\n\t" "nop\n\t"
				"nop\n\t" "nop\n\t"
				"nop\n\t" "nop\n\t"
				"nop\n\t" "nop\n\t"
				"mov %0, %%eax\n\t"
				: "=r" (OpIoStruct->ReadFromPort)
                                : "r" (OpIoStruct->PortAddr)
			);
			rw = 'r';
			printk
			(
				KERN_INFO 
				"\nIOTranslator v1.0: in eax, dx\n" 
				"IOTranslator v1.0: eax [Data from Port] = 0x%x\n"
				"IOTranslator v1.0: dx [Addr Port] = 0x%x\n"
				"IOTranslator v1.0: [%c]\n",
				OpIoStruct->ReadFromPort, OpIoStruct->PortAddr, rw
			);
			break;
		default:
			printk(KERN_INFO "\nIOTranslator v1.0: Error," 
					 " wrong number MODE [0x%x]\n", OpIoStruct->Mode);
			OpIoStruct->Identifi = ZERO;
			OpIoStruct->Mode = ZERO;
			break;
		}
		OpIoStruct->Identifi = ZERO;
		OpIoStruct->Mode = ZERO;
		printk(KERN_INFO "\nIOTranslator v1.0: Branch with IDENTIFI is complete\n");
	}
	else 
	{
		printk(KERN_INFO "\nIOTranslator v1.0: Error, wrong IDENTIFI [0x%x]\n", OpIoStruct->Identifi);
		OpIoStruct->Identifi = ZERO;
		OpIoStruct->Mode = ZERO;
	}
	printk(KERN_INFO "\nIOTranslator v1.0: WriteToDevIOTranslator function is complete\n");
	return sizebuf;
}

static int __init IOTranslator_Init(void)
{
	alloc_chrdev_region(&Dev_t, DEVFIRST, DEVCOUNT, MODULNAME);

	Major = MAJOR(Dev_t);
	Minor = MINOR(Dev_t);

	Cdev = cdev_alloc();
	cdev_init(Cdev, &FileOperations);
	cdev_add(Cdev, Dev_t, DEVCOUNT);

	DevClass = class_create(THIS_MODULE, "dyn_class");
	device_create(DevClass, NULL, Dev_t, "%s", DEVNAME);

	printk(KERN_INFO "\nIOTranslator v1.0: Module initialization completed."
			 " Major = %d, Minor = %d\n", Major, Minor);
	return 0;
}

static void __exit IOTranslator_Exit(void)
{
	device_destroy(DevClass, Dev_t);
	class_destroy(DevClass);
	cdev_del(Cdev);
	unregister_chrdev_region(Dev_t, DEVCOUNT);
	printk(KERN_INFO "\nIOTranslator v1.0: Module deletion completed\n");
}
