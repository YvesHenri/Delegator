#include <stdio.h>

#include "..\Includes\Delegate\Delegate.h"

void freeFunction()
{
	printf("freeFunction! \n");
}

class Clazz
{
public:
	void memberFunction()
	{
		printf("memberFunction! \n");
	}

	void memberConstFunction() const
	{
		printf("memberConstFunction! \n");
	}
};

int main()
{
	{
		Clazz clazz;
		Delegate<void(void)> d;

		d.reset(&freeFunction);
		d.invoke();
		d.reset(&Clazz::memberFunction, &clazz);
		d.invoke();
		d.reset(&Clazz::memberConstFunction, &clazz);
		d.invoke();
	}

    return getchar();
}

