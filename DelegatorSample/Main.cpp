#include <stdio.h>
#include <Delegate.h>

#include "Clazz.h"

void member()
{
	Clazz clazz;

	Delegate<void()> staticFunctionDelegate(&Clazz::staticMemberFunction);
	Delegate<void()> memberFunctionDelegate(&Clazz::memberFunction, &clazz);
	Delegate<void()> memberConstFunctionDelegate(&Clazz::memberConstFunction, &clazz);

	staticFunctionDelegate.invoke();
	memberFunctionDelegate.invoke();
	memberConstFunctionDelegate.invoke();
}

void free()
{
	Delegate<void()> freeFunctionDelegate(&member);

	// This will trigger the member functions example
	freeFunctionDelegate.invoke();
}

int main()
{
	free();

	return getchar();
}