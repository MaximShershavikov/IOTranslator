![Эмблема](https://user-images.githubusercontent.com/46265118/54478466-84c3f200-4823-11e9-8001-c638b4012832.png)

This program allows you to read/write data to the I/O ports of devices from the user space of the OS Linux. To do this, the program executes the assembler in/out commands in the Linux kernel.

![Предупреждение](https://user-images.githubusercontent.com/46265118/54478652-b047dc00-4825-11e9-8334-5ad13caee21b.png)

![skrin](https://user-images.githubusercontent.com/46265118/63090994-ac9bbb00-bf65-11e9-8ea9-6cea2cbf4e61.png)

System requirements: 
- OS Ubuntu 14, Ubuntu 16, may work in other versions of the Ubuntu operating system
- x86 or x64 processor architecture

When the program is first launched, a module is compiled for a particular Linux kernel. To compile a module, you must have a gcc compiler in the operating system. If there is no compiler then it must be installed. In Ubuntu, to install the compiler, you must enter the command: sudo apt-get install gcc.

To run the program, you need to go to the root directory. To do this, enter command: "cd /....../IOTranslator-v1.0/IOTranslator-v1.0_x86/" or "cd /....../IOTranslator-v1.0/IOTranslator-v1.0_x64/". After going to the root directory of the program, you must enter command: "sudo ./IOTranslator_v1.0.out".

If after entering "./IOTranslator_v1.0.out" you received message "./IOTranslator_v1.0.out: permission denied". To correct this situation, you need to enter command: "chmod +x IOTranslator_v1.0.out ./IOTranslator_v1.0.out". After that, you need to restart the program by entering command: "./IOTranslator_v1.0.out".
