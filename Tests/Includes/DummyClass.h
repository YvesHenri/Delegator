#ifndef DUMMY_CLASS_H
#define DUMMY_CLASS_H

/// Free functions
void freeFunction();
void freeFunction2();

/// Member functions
class DummyClass
{
public:
	void memberFunction();
	void memberConstFunction() const;
	static void staticMemberFunction();
};

#endif