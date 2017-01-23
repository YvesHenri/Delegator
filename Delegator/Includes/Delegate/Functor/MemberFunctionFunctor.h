#ifndef MEMBER_FUNCTION_FUNCTOR_H
#define MEMBER_FUNCTION_FUNCTOR_H

#include "Functor.h"

// Non specialized template declaration (empty)
template <typename>
class MemberFunctionFunctor;

// Specialization for member functions functors
template <class TClass, typename TReturn, typename... TArgs>
class MemberFunctionFunctor<TReturn(TClass::*)(TArgs...)> final : public Functor<TReturn(TArgs...)>
{
private:
	using MemberInstance = TClass*;
	using MemberFunction = TReturn(TClass::*)(TArgs...);

public:
	explicit MemberFunctionFunctor(const MemberFunction function, const MemberInstance instance);
	~MemberFunctionFunctor();

	//bool operator == (const Functor& functor) override;

	TReturn operator ()(TArgs&&... args) override;

private:
	const MemberInstance m_instance;
	const MemberFunction m_function;
};

#include "Inline\MemberFunctionFunctor.inl"

#endif