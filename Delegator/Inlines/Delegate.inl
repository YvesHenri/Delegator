#ifndef DELEGATE_IMPL
#define DELEGATE_IMPL

template <typename TReturn, typename... TArgs>
Delegate<TReturn(TArgs...)>::Delegate()
{
	reset();
}

template <typename TReturn, typename... TArgs>
Delegate<TReturn(TArgs...)>::Delegate(TReturn(*freeFunction)(TArgs...))
{
	reset(freeFunction);
}

template <typename TReturn, typename... TArgs>
template <class TClass>
Delegate<TReturn(TArgs...)>::Delegate(TReturn(TClass::*memberFunction)(TArgs...), TClass* instance)
{
	reset(memberFunction, instance);
}

template <typename TReturn, typename... TArgs>
template <class TClass>
Delegate<TReturn(TArgs...)>::Delegate(TReturn(TClass::*memberConstFunction)(TArgs...) const, TClass* instance)
{
	reset(memberConstFunction, instance);
}

template <typename TReturn, typename... TArgs>
void Delegate<TReturn(TArgs...)>::reset()
{
	m_functor.reset();
}

template <typename TReturn, typename... TArgs>
void Delegate<TReturn(TArgs...)>::reset(Delegate* delegate)
{
	m_functor = delegate->m_functor;
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

template <typename TReturn, typename... TArgs>
TReturn Delegate<TReturn(TArgs...)>::invoke(TArgs&... args)
{
	if (!m_functor)
		throw UnboundDelegateException();

	return m_functor->operator()(std::forward<TArgs>(args)...);
}

template <typename TReturn, typename... TArgs>
bool Delegate<TReturn(TArgs...)>::operator==(const Delegate<TReturn(TArgs...)>& delegate)
{
	TFunctor* self = m_functor.get();
	TFunctor* target = delegate.m_functor.get();

	bool areBothEmpty = self == nullptr && target == nullptr;
	bool areBothValid = self != nullptr && target != nullptr;
	bool areBothEqual = areBothValid && (*self == *target);

	return areBothEmpty || areBothEqual;
}

#endif