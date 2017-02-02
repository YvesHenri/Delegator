#ifndef MACROS_H
#define MACROS_H

#include "..\Includes\LoggableDelegate.h"

#define COMPARE(d1, d2) compare(#d1, #d2, d1, d2)

void compare(char* d1n, char* d2n, LoggableDelegate<void(void)>& d1, LoggableDelegate<void(void)>& d2)
{
	printf("%s == %s: %s \n", d1n, d2n, d1 == d2 ? "TRUE!" : "false");
}

#endif