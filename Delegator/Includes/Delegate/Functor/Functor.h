#ifndef FUNCTOR_H
#define FUNCTOR_H

#include "..\Exception\UnboundDelegateException.h"

// Non specialized template declaration for a functor (empty)
template <typename>
class Functor;

// Specialization for a functor
template <typename TReturn, typename... TArgs>
class Functor<TReturn(TArgs...)>
{
public:
	virtual bool operator !() = 0;
	//virtual bool operator == (const Functor& functor) = 0;

	virtual TReturn operator()(TArgs&&... args) = 0;
};

#endif