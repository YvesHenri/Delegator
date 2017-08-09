#ifndef DELEGATE_H
#define DELEGATE_H

#include <memory>

#include "Macros.h"
#include "Functor\FreeFunctionFunctor.h"
#include "Functor\MemberFunctionFunctor.h"
#include "Functor\MemberConstFunctionFunctor.h"

// Non specialized template declaration for a delegate (empty)
template <typename>
class Delegate;

// Specialization for a delegate
template <typename TReturn, typename... TArgs>
class DELEGATOR_API Delegate<TReturn(TArgs...)> final
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
	TReturn invoke(TArgs&... args);

	// Checks whether both delegates point to the same function
	bool operator == (const Delegate<TReturn(TArgs...)>& delegate);

private:
	TFunctorSharedPtr m_functor;
};

#include "..\Inlines\Delegate.inl"

#endif