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

static void AbautProgram();

int main(int argv, char *argc[])
{
    printf
	(
		"**********************************************************\n\n"
	    "                     IOTranslator v1.0                    \n\n"
		"**********************************************************\n"
	);

	char *mode;
	InOutRouting io;

	mode = new char[3];
	mode[0] = 0;
	mode[1] = 0;
	mode[2] = 0;

	if (io.err)
	{
		delete[] mode;
		mode = nullptr;
		return 0;
	}

	printf
	(
		"IOTranslator v1.0. Enter [ w ] to write data to the port\n"
		"IOTranslator v1.0. Enter [ r ] to read data from port\n"
		"IOTranslator v1.0. Enter [ a ] to read program information\n"
		"IOTranslator v1.0. Enter [ e ] to exit the program\n"
		"IOTranslator v1.0. WARNING: Issuance of assembler commands\n"
		"[in] and [out] from user space is not recommended, it can\n"
		"harm the operating system. You must be careful. Before using\n"
		"this program, you must understand what you are doing\n"
		"You use this program at your own risk. This program works\n"
		"only with INTEL processor architecture\n"
	);

	do
	{
		printf("-----------------------------------------------------------\n");
		printf("IOTranslator v1.0. Enter the mode: ");
		scanf("%s", mode);
		if (!strcmp(mode, "*$*"))
		{
			break;
		}
		if (!strcmp(mode, "a"))
		{
			AbautProgram();
			mode[0] = '*';
			mode[1] = '$';
			mode[2] = '*';
			continue;
		}
		if (strcmp(mode, "e"))
		{
			io = *mode;
			mode[0] = '*';
			mode[1] = '$';
			mode[2] = '*';
		}
	} while (strcmp(mode, "e"));

	delete[] mode;
	mode = nullptr;
	printf("IOTranslator v1.0. Closed\n");
    return 0;
}

static void AbautProgram()
{
	printf
	(
		"IOTranslator version 1.0. Program for writing and reading to input/output ports.\n"
		"Copyright (C) 2019  Maxim Shershavikov\n\n"
		"This file is part of IOTranslator v1.0.\n\n"
		"IOTranslator v1.0 is free software: you can redistribute it and/or modify\n"
		"it under the terms of the GNU General Public License as published by\n"
		"the Free Software Foundation, either version 3 of the License, or\n"
		"(at your option) any later version.\n\n"
		"IOTranslator v1.0 is distributed in the hope that it will be useful,\n"
		"but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
		"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
		"GNU General Public License for more details.\n\n"
		"You should have received a copy of the GNU General Public License\n"
		"along with this program.  If not, see <https://www.gnu.org/licenses/>.\n\n"
		"Email m.shershavikov@yandex.ru\n"
	);
}