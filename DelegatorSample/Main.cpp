#include <stdio.h>
#include "Delegate.h"

int meep()
{
	return 123;
}

int main()
{
	Delegate<int()> temp(&meep);

	printf("Result: %d\n", temp.invoke());

	return getchar();
}