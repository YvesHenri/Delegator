#include <stdio.h>

#include "..\Includes\Delegate\Delegate.h"

#pragma region Tests

void freeFunction()
{
	printf("> Called freeFunction! \n");
}

class Clazz
{
public:
	void memberFunction()
	{
		printf("> Called memberFunction! \n");
	}

	void memberConstFunction() const
	{
		printf("> Called memberConstFunction! \n");
	}

	static void staticMemberFunction() {
		printf("> Called staticMemberFunction! \n");
	}
};

#pragma endregion

int main()
{
	Clazz clazz;

	{
		Delegate<void(void)> d1;

		{
			Delegate<void(void)> d2;

			d2.reset(&freeFunction);
			d2.invoke();
			d2.reset(&Clazz::memberFunction, &clazz);
			d2.invoke();
			d2.reset(&Clazz::memberConstFunction, &clazz);
			d2.invoke();
			d2.reset(&Clazz::staticMemberFunction);
			d2.invoke();
			d1.reset(&d2);
		}

		d1.invoke();
	}

    return getchar();
}

