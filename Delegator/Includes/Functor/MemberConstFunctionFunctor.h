#ifndef MEMBER_CONST_FUNCTION_FUNCTOR_H
#define MEMBER_CONST_FUNCTION_FUNCTOR_H

#include "Macros.h"
#include "Functor.h"

// Non specialized template declaration (empty)
template <typename>
class MemberConstFunctionFunctor;

// Specialization for member const functions
template <class TClass, typename TReturn, typename... TArgs>
class DELEGATOR_API MemberConstFunctionFunctor<TReturn(TClass::*)(TArgs...) const> final : public Functor<TReturn(TArgs...)>
{
private:
	using MemberConstInstance = const TClass*;
	using MemberConstFunction = TReturn(TClass::*)(TArgs...) const;

public:
	explicit MemberConstFunctionFunctor(const MemberConstFunction function, const MemberConstInstance instance);
	~MemberConstFunctionFunctor() = default;

	bool operator==(const Functor<TReturn(TArgs...)>& functor) override;
	TReturn operator()(TArgs&&... args) override;

private:
	const MemberConstInstance m_instance;
	const MemberConstFunction m_function;
};

#include "..\Inlines\Functor\MemberConstFunctionFunctor.inl"

#endif