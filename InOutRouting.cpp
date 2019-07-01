/*************************************************************************************

	IOTranslator version 1.0. Program for writing and reading to input/output ports. 
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
	
*************************************************************************************/

#include "InOutRouting.h"

InOutRouting::InOutRouting() : res(0), text(new char), OpIoStruct(new InOut_Operations), op(nullptr), count(0)
{
	if (!(op = fopen("ModulIOTranslator.ko", "rb")))
	{
		popen("make -C /lib/modules/$(uname -r)/build M=$PWD modules", "r");
		printf("IOTranslator v1.0. Processing, Please wait\n");

		while (count != DELAY)
		{
			if (op = fopen("ModulIOTranslator.ko", "rb"))
			{
				printf("IOTranslator v1.0. Module completed\n");
				fclose(op);
				break;
			}
			count++;
		}
		if (count == DELAY) printf("IOTranslator v1.0. Modul das not compiling\n");
	}

	if (!(op = fopen("/dev/VirtualDevIOTranslator", "r+")))
	{
		if (!(op = fopen("ModulIOTranslator.ko", "rb")))
		{
			err = true;
			printf("IOTranslator v1.0. ModulIOTranslator.ko not found\n");
			return;
		}
		else { fclose(op); op = nullptr; }

		popen("sudo insmod ModulIOTranslator.ko", "r");
		for (int i = 0; i < DELAY; i++) asm volatile("nop");
		printf("IOTranslator v1.0. Module with a virtual device installed\n");
	}
	else { fclose(op); printf("IOTranslator v1.0. VirtualDevice found\n"); }
	err = false;
}

InOutRouting::~InOutRouting()
{
	delete OpIoStruct;
	OpIoStruct = nullptr;
	delete text;
	text = nullptr;
	res = 0;
	op = nullptr;
	count = 0;
	printf("IOTranslator v1.0. Exit\n");
}

void InOutRouting::InitNull(int n)
{
	switch (n)
	{
	case 0:
		OpIoStruct->Identifi = IDENTIFI;
		OpIoStruct->PortAddr = 0;
		OpIoStruct->WriteToPort = 0;
		OpIoStruct->ReadFromPort = 0;
		OpIoStruct->Mode = WRITEPORT;
		break;
	case 1:
		OpIoStruct->Identifi = IDENTIFI;
		OpIoStruct->PortAddr = 0;
		OpIoStruct->WriteToPort = 0;
		OpIoStruct->ReadFromPort = 0;
		OpIoStruct->Mode = READPORT;
		break;
	case 2:
		OpIoStruct->Identifi = 0;
		OpIoStruct->PortAddr = 0;
		OpIoStruct->WriteToPort = 0;
		OpIoStruct->ReadFromPort = 0;
		OpIoStruct->Mode = 0;
		break;
	}
}

void InOutRouting::OutWrite()
{
	*text = 'n';
	InitNull(0);
	do
	{
		printf("IOTranslator v1.0. Enter the port address: 0x");
		res = scanf("%hx", &(OpIoStruct->PortAddr));
		if (res != 1)
		{
			scanf("%*[^\r\n]");
			OpIoStruct->PortAddr = 0;
			printf("IOTranslator v1.0. Incorrect value, re-enter\n");
		}
	} while (!res);

	do
	{
		printf("IOTranslator v1.0. Enter data to port: 0x");
		res = scanf("%lx", &(OpIoStruct->WriteToPort));
		if (res != 1)
		{
			scanf("%*[^\r\n]");
			OpIoStruct->WriteToPort = 0;
			printf("IOTranslator v1.0. Incorrect value, re-enter\n");
		}
	} while (!res);
	printf("IOTranslator v1.0. Are you sure you want to write data to the port?\n");
	
	do
	{
		printf("IOTranslator v1.0. Enter [y] if yes or [n] if no: ");
		scanf("%s", text);
		if (!strcmp(text, "n"))
		{
			InitNull(2);
			printf("IOTranslator v1.0. Data writing to port canceled\n");
			return;
		}
		if (strcmp(text, "y") && strcmp(text, "n"))
			printf("IOTranslator v1.0. Incorrect character entered, re-enter\n");
	} while (strcmp(text, "y"));
	
	op = fopen("/dev/VirtualDevIOTranslator", "r+");
	fwrite(OpIoStruct, sizeof(InOut_Operations), 1, op);
	fread(OpIoStruct, sizeof(InOut_Operations), 1, op);
	fclose(op);

	printf("IOTranslator v1.0. Sending data to port is complete\n");
	InitNull(2);
}

void InOutRouting::InRead()
{
	*text = 'n';
	InitNull(1);
	do
	{
		printf("IOTranslator v1.0. Enter the port address: 0x");
		res = scanf("%hx", &(OpIoStruct->PortAddr));
		if (res != 1)
		{
			scanf("%*[^\r\n]");
			OpIoStruct->PortAddr = 0;
			printf("IOTranslator v1.0. Incorrect value, re-enter\n");
		}
	} while (!res);
	printf("IOTranslator v1.0. Are you sure you want to read data from the port?\n");

	do
	{
		printf("IOTranslator v1.0. Enter [y] if yes or [n] if no: ");
		scanf("%s", text);
		if (!strcmp(text, "n"))
		{
			InitNull(2);
			printf("IOTranslator v1.0. Reading data from the port is canceled\n");
			return;
		}
		if (strcmp(text, "y") && strcmp(text, "n"))
			printf("IOTranslator v1.0. Incorrect character entered, re-enter\n");
	} while (strcmp(text, "y"));

	op = fopen("/dev/VirtualDevIOTranslator", "r+");
	fwrite(OpIoStruct, sizeof(InOut_Operations), 1, op);
	fread(OpIoStruct, sizeof(InOut_Operations), 1, op);
	fclose(op);

	printf("IOTranslator v1.0. Data read from the port: 0x%x\n", OpIoStruct->ReadFromPort);
	InitNull(2);
}

char InOutRouting::operator=(char &mode)
{
	if (!(strcmp(&mode, "w"))) OutWrite();
	if (!(strcmp(&mode, "r"))) InRead();
	if (strcmp(&mode, "w") && strcmp(&mode, "r"))
		printf("IOTranslator v1.0. Incorrect mode entered\n");
	return mode;
}