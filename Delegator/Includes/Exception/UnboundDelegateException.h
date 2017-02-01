#ifndef UNBOUND_DELEGATE_EXCEPTION_H
#define UNBOUND_DELEGATE_EXCEPTION_H

#include <stdio.h> // Debug
#include <exception>

class UnboundDelegateException final : public std::exception
{
public:
	UnboundDelegateException() : std::exception("Unbound delegate")
	{}

	UnboundDelegateException(const char* const message) : std::exception(message)
	{}
};

#endif