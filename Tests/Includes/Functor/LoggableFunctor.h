#ifndef LOGGABLE_FUNCTOR_H
#define LOGGABLE_FUNCTOR_H

#include <stdio.h>
#include <string>
#include <memory>
#include <assert.h>

#include "..\..\..\Delegator\Includes\Functor\Functor.h"

// Non specialized template declaration for loggable functors (empty)
template <typename>
class LoggableFunctor;

// Specialization for loggable functors
template <typename TReturn, typename... TArgs>
class LoggableFunctor<TReturn(TArgs...)> final
{
public:
	LoggableFunctor(std::string label, Functor<TReturn(TArgs...)>* unloggableFunctor);
	~LoggableFunctor();

	bool	operator ==(const LoggableFunctor<TReturn(TArgs...)>& loggableFunctor);
	TReturn operator ()(TArgs&&... args);

private:
	std::string m_label;
	std::shared_ptr<Functor<TReturn(TArgs...)>> m_unloggableFunctor;
};

#include "Inline\LoggableFunctor.inl"

#endif