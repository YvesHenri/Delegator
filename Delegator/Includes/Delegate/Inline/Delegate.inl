#ifndef DELEGATE_IMPL
#define DELEGATE_IMPL

template <typename TReturn, typename... TArgs>
TReturn Delegate<TReturn(TArgs...)>::invoke(TArgs&&... args)
{
	if (!m_functor)
		throw UnboundDelegateException();

	m_functor->operator()(std::forward<TArgs>(args)...);
}

template <typename TReturn, typename... TArgs>
void Delegate<TReturn(TArgs...)>::reset()
{
	m_functor.reset();
}

template <typename TReturn, typename... TArgs>
void Delegate<TReturn(TArgs...)>::reset(TReturn(*freeFunction)(TArgs...))
{
	m_functor.reset(new FreeFunctionFunctor<TReturn(TArgs...)>(freeFunction));
}

template <typename TReturn, typename... TArgs>
template <typename TClass>
void Delegate<TReturn(TArgs...)>::reset(TReturn(TClass::*memberFunction)(TArgs...), TClass* instance)
{
	m_functor.reset(new MemberFunctionFunctor<TReturn(TClass::*)(TArgs...)>(memberFunction, instance));
}

template <typename TReturn, typename... TArgs>
template <typename TClass>
void Delegate<TReturn(TArgs...)>::reset(TReturn(TClass::*memberConstFunction)(TArgs...) const, TClass* instance)
{
	m_functor.reset(new MemberConstFunctionFunctor<TReturn(TClass::*)(TArgs...) const>(memberConstFunction, instance));
}

#endif