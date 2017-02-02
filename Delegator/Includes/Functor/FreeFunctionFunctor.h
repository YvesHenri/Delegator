#ifndef FREE_FUNCTION_FUNCTOR_H
#define FREE_FUNCTION_FUNCTOR_H

#include "Functor.h"

// Non specialized template declaration for a free function functor (empty)
template <typename>
class FreeFunctionFunctor;

// Specialization for free functions functor
template <typename TReturn, typename... TArgs>
class FreeFunctionFunctor<TReturn(TArgs...)> final : public Functor<TReturn(TArgs...)>
{
private:
	using FreeFunction = TReturn(*)(TArgs...);

public:
	explicit FreeFunctionFunctor(const FreeFunction function);
	~FreeFunctionFunctor() = default;

	bool	operator ==(const Functor<TReturn(TArgs...)>& functor) override;
	TReturn operator ()(TArgs&&... args) override;

private:
	const FreeFunction m_function;
};

#include "Inline\FreeFunctionFunctor.inl"

#endif