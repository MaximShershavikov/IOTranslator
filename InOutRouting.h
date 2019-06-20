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

#ifndef __IOOUTROUTING__
#define __IOOUTROUTING__

#include <cstdio>
#include <string.h>

#define IDENTIFI  0x1AF652D8
#define WRITEPORT 0x10FFE701
#define READPORT  0x20AA3302
#define DELAY 100000000

class InOutRouting
{
private:
	int res;
	char *text;
	struct InOut_Operations
	{
		unsigned int Identifi;
		unsigned short PortAddr;
		unsigned int WriteToPort;
		unsigned int ReadFromPort;
		unsigned int Mode;
	} *OpIoStruct;
	FILE *op;
	unsigned int count;
	void InitNull(int n);
	void OutWrite();
	void InRead();
public:
	bool err;
	InOutRouting();
	~InOutRouting();
	char operator=(char &mode);
};

#endif // __IOOUTROUTING__