#include <stdio.h>
#include "Clazz.h"

void Clazz::memberFunction()
{
	printf("----> Called memberFunction! \n");
}

void Clazz::memberConstFunction() const
{
	printf("----> Called memberConstFunction! \n");
}

void Clazz::staticMemberFunction() {
	printf("----> Called staticMemberFunction! \n");
}