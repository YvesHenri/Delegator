#include <stdio.h>
#include "..\Includes\DummyClass.h"

void freeFunction()
{
	printf("----> Called freeFunction! \n");
}

void freeFunction2()
{
	printf("----> Called freeFunction TWO! \n");
}

void DummyClass::memberFunction()
{
	printf("----> Called memberFunction! \n");
}

void DummyClass::memberConstFunction() const
{
	printf("----> Called memberConstFunction! \n");
}

void DummyClass::staticMemberFunction() {
	printf("----> Called staticMemberFunction! \n");
}