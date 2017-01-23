#include <stdio.h>
#include <functional>

#include "..\Includes\Delegate\Delegate.h"

#define COMPARE(d1, d2) compare(#d1, #d2, d1, d2)
void compare(char* d1n, char* d2n, Delegate<void(void)>& d1, Delegate<void(void)>& d2)
{
	printf("%s == %s: %s \n", d1n, d2n, d1 == d2 ? "TRUE!" : "false");
}

#pragma region Tests

void freeFunction()
{
	printf("> Called freeFunction! \n");
}

void freeFunction2()
{
	printf("> Called freeFunction TWO! \n");
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

void runResetsTest()
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

			printf("@@@ End of scope 1.1 @@@ \n");
		}

		d1.invoke();

		printf("@@@ End of scope 1 @@@ \n");
	}

	{
		Delegate<void(void)> d1(&Clazz::memberFunction, &clazz);

		d1.invoke();

		printf("@@@ End of scope 2 @@@ \n");
	}
}

void runCyclicResetTest()
{
	Delegate<void(void)> d1;
	Delegate<void(void)> d2;

	d1.reset(&freeFunction);
	d2.reset(&d1);
	d1.reset(&d2);

	d1.invoke();
	d2.invoke();
}

void runEqualityTest()
{
	Clazz clazz;

	Delegate<void(void)> d1(&freeFunction);
	Delegate<void(void)> d2(&freeFunction);
	Delegate<void(void)> d3(&freeFunction2);
	Delegate<void(void)> d4(&freeFunction2);
	Delegate<void(void)> d5(&Clazz::staticMemberFunction);
	Delegate<void(void)> d6(&Clazz::staticMemberFunction);
	Delegate<void(void)> d7(&Clazz::memberFunction, &clazz);
	Delegate<void(void)> d8(&Clazz::memberFunction, &clazz);
	Delegate<void(void)> d9(&Clazz::memberConstFunction, &clazz);
	Delegate<void(void)> d10(&Clazz::memberConstFunction, &clazz);
	Delegate<void(void)> d11;

	COMPARE(d1, d2);
	COMPARE(d1, d3);
	COMPARE(d1, d4);
	COMPARE(d1, d5);
	COMPARE(d1, d6);
	COMPARE(d1, d7); //
	COMPARE(d1, d8);
	COMPARE(d1, d9);
	COMPARE(d1, d10);
	COMPARE(d1, d11);
	printf("---------- End of d1 ---------- \n");
	COMPARE(d2, d1);
	COMPARE(d2, d3);
	COMPARE(d2, d4);
	COMPARE(d2, d5);
	COMPARE(d2, d6);
	COMPARE(d2, d7);
	COMPARE(d2, d8);
	COMPARE(d2, d9);
	COMPARE(d2, d10);
	COMPARE(d2, d11);
	printf("---------- End of d2 ---------- \n");
	COMPARE(d3, d2);
	COMPARE(d3, d1);
	COMPARE(d3, d4);
	COMPARE(d3, d5);
	COMPARE(d3, d6);
	COMPARE(d3, d7);
	COMPARE(d3, d8);
	COMPARE(d3, d9);
	COMPARE(d3, d10);
	COMPARE(d3, d11);
	printf("---------- End of d3 ---------- \n");
	COMPARE(d4, d2);
	COMPARE(d4, d3);
	COMPARE(d4, d1);
	COMPARE(d4, d5);
	COMPARE(d4, d6);
	COMPARE(d4, d7);
	COMPARE(d4, d8);
	COMPARE(d4, d9);
	COMPARE(d4, d10);
	COMPARE(d4, d11);
	printf("---------- End of d4 ---------- \n");
	COMPARE(d5, d2);
	COMPARE(d5, d3);
	COMPARE(d5, d4);
	COMPARE(d5, d1);
	COMPARE(d5, d6);
	COMPARE(d5, d7);
	COMPARE(d5, d8);
	COMPARE(d5, d9);
	COMPARE(d5, d10);
	COMPARE(d5, d11);
	printf("---------- End of d5 ---------- \n");
	COMPARE(d6, d2);
	COMPARE(d6, d3);
	COMPARE(d6, d4);
	COMPARE(d6, d5);
	COMPARE(d6, d1);
	COMPARE(d6, d7);
	COMPARE(d6, d8);
	COMPARE(d6, d9);
	COMPARE(d6, d10);
	COMPARE(d6, d11);
	printf("---------- End of d6 ---------- \n");
	COMPARE(d7, d2);
	COMPARE(d7, d3);
	COMPARE(d7, d4);
	COMPARE(d7, d5);
	COMPARE(d7, d6);
	COMPARE(d7, d1);
	COMPARE(d7, d8);
	COMPARE(d7, d9);
	COMPARE(d7, d10);
	COMPARE(d7, d11);
	printf("---------- End of d7 ---------- \n");
	COMPARE(d8, d2);
	COMPARE(d8, d3);
	COMPARE(d8, d4);
	COMPARE(d8, d5);
	COMPARE(d8, d6);
	COMPARE(d8, d7);
	COMPARE(d8, d1);
	COMPARE(d8, d9);
	COMPARE(d8, d10);
	COMPARE(d8, d11);
	printf("---------- End of d8 ---------- \n");
	COMPARE(d9, d2);
	COMPARE(d9, d3);
	COMPARE(d9, d4);
	COMPARE(d9, d5);
	COMPARE(d9, d6);
	COMPARE(d9, d7);
	COMPARE(d9, d8);
	COMPARE(d9, d1);
	COMPARE(d9, d10);
	COMPARE(d9, d11);
	printf("---------- End of d9 ---------- \n");
	COMPARE(d10, d2);
	COMPARE(d10, d3);
	COMPARE(d10, d4);
	COMPARE(d10, d5);
	COMPARE(d10, d6);
	COMPARE(d10, d7);
	COMPARE(d10, d8);
	COMPARE(d10, d9);
	COMPARE(d10, d1);
	COMPARE(d10, d11);
	printf("---------- End of d10 ---------- \n");
	COMPARE(d11, d2);
	COMPARE(d11, d3);
	COMPARE(d11, d4);
	COMPARE(d11, d5);
	COMPARE(d11, d6);
	COMPARE(d11, d7);
	COMPARE(d11, d8);
	COMPARE(d11, d9);
	COMPARE(d11, d10);
	COMPARE(d11, d1);
	printf("---------- End of d11 ---------- \n");
}

int main()
{
	//runResetsTest();
	//runCyclicResetTest();
	runEqualityTest();

    return getchar();
}

