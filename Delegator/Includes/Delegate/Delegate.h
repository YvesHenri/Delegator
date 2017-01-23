#ifndef DELEGATE_H
#define DELEGATE_H

#include <memory>

#include "Functor\FreeFunctionFunctor.h"
#include "Functor\MemberFunctionFunctor.h"
#include "Functor\MemberConstFunctionFunctor.h"

// Non specialized template declaration for a delegate (empty)
template <typename>
class Delegate;

// Specialization for a delegate
template <typename TReturn, typename... TArgs>
class Delegate<TReturn(TArgs...)> final
{
private:
	using DynamicFunctor = Functor<TReturn(TArgs...)>;
	using DynamicFunctorPointer = std::shared_ptr<DynamicFunctor>;

public:
	Delegate() = default;
	~Delegate() = default;

	// Invokes this delegate
	TReturn invoke(TArgs&&... args);

	// Resets this delegate to its initial state (null)
	void reset();

	// Resets this delegate to a new free/static function
	void reset(TReturn(*freeFunction)(TArgs...));

	// Resets this delegate to a new member function
	template <class TClass>
	void reset(TReturn(TClass::*memberFunction)(TArgs...), TClass* instance);

	// Resets this delegate to a new member const function
	template <class TClass>
	void reset(TReturn(TClass::*memberConstFunction)(TArgs...) const, TClass* instance);

private:
	DynamicFunctorPointer m_functor;
};

#include "Inline\Delegate.inl"

#endif