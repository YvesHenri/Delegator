#ifndef LOGGABLE_DELEGATE_H
#define LOGGABLE_DELEGATE_H

#include <memory>

#include "..\..\Delegate\Functor\FreeFunctionFunctor.h"
#include "..\..\Delegate\Functor\MemberFunctionFunctor.h"
#include "..\..\Delegate\Functor\MemberConstFunctionFunctor.h"

// Non specialized template declaration for a delegate (empty)
template <typename>
class LoggableDelegate;

// Specialization for a delegate
template <typename TReturn, typename... TArgs>
class LoggableDelegate<TReturn(TArgs...)> final
{
private:
	using TFunctor = Functor<TReturn(TArgs...)>;
	using TFunctorSharedPtr = std::shared_ptr<TFunctor>;

public:
	// Creates an unbound (empty) delegate
	Delegate();

	// Creates a delegate from a free/static function
	Delegate(TReturn(*freeFunction)(TArgs...));

	// Creates a delegate from a member function
	template <class TClass>
	Delegate(TReturn(TClass::*memberFunction)(TArgs...), TClass* instance);

	// Creates a delegate from a member const function
	template <class TClass>
	Delegate(TReturn(TClass::*memberFunction)(TArgs...) const, TClass* instance);

	// Resets this delegate to its unboud state (empty)
	void reset();

	// Resets this delegate to a given delegate's state
	void reset(Delegate* delegate);

	// Resets this delegate to a new free/static function
	void reset(TReturn(*freeFunction)(TArgs...));

	// Resets this delegate to a new member function
	template <class TClass>
	void reset(TReturn(TClass::*memberFunction)(TArgs...), TClass* instance);

	// Resets this delegate to a new member const function
	template <class TClass>
	void reset(TReturn(TClass::*memberConstFunction)(TArgs...) const, TClass* instance);

	// Invokes this delegate
	TReturn invoke(TArgs&&... args);

	// Checks whether both delegates point to the same function
	bool operator == (const Delegate& delegate);

private:
	TFunctorSharedPtr m_functor;
};

#include "Inline\LoggableDelegate.inl"

#endif