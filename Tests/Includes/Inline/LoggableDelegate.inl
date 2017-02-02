#ifndef LOGGABLE_DELEGATE_IMPL
#define LOGGABLE_DELEGATE_IMPL

template <typename TReturn, typename... TArgs>
LoggableDelegate<TReturn(TArgs...)>::LoggableDelegate()
{
	reset();
}

template <typename TReturn, typename... TArgs>
LoggableDelegate<TReturn(TArgs...)>::LoggableDelegate(TReturn(*freeFunction)(TArgs...))
{
	reset(freeFunction);
}

template <typename TReturn, typename... TArgs>
template <class TClass>
LoggableDelegate<TReturn(TArgs...)>::LoggableDelegate(TReturn(TClass::*memberFunction)(TArgs...), TClass* instance)
{
	reset(memberFunction, instance);
}

template <typename TReturn, typename... TArgs>
template <class TClass>
LoggableDelegate<TReturn(TArgs...)>::LoggableDelegate(TReturn(TClass::*memberConstFunction)(TArgs...) const, TClass* instance)
{
	reset(memberConstFunction, instance);
}

template <typename TReturn, typename... TArgs>
void LoggableDelegate<TReturn(TArgs...)>::reset()
{
	m_functor.reset();
}

template <typename TReturn, typename... TArgs>
void LoggableDelegate<TReturn(TArgs...)>::reset(LoggableDelegate* delegate)
{
	m_functor = delegate->m_functor;
}

template <typename TReturn, typename... TArgs>
void LoggableDelegate<TReturn(TArgs...)>::reset(TReturn(*freeFunction)(TArgs...))
{
	Functor<TReturn(TArgs...)>* unloggableFunctor = new FreeFunctionFunctor<TReturn(TArgs...)>(freeFunction);

	m_functor.reset(new LoggableFunctor<TReturn(TArgs...)>("FreeFunctionFunctor", unloggableFunctor));
}

template <typename TReturn, typename... TArgs>
template <typename TClass>
void LoggableDelegate<TReturn(TArgs...)>::reset(TReturn(TClass::*memberFunction)(TArgs...), TClass* instance)
{
	Functor<TReturn(TArgs...)>* unloggableFunctor = new MemberFunctionFunctor<TReturn(TClass::*)(TArgs...)>(memberFunction, instance);

	m_functor.reset(new LoggableFunctor<TReturn(TArgs...)>("MemberFunctionFunctor", unloggableFunctor));
}

template <typename TReturn, typename... TArgs>
template <typename TClass>
void LoggableDelegate<TReturn(TArgs...)>::reset(TReturn(TClass::*memberConstFunction)(TArgs...) const, TClass* instance)
{
	Functor<TReturn(TArgs...)>* unloggableFunctor = new MemberConstFunctionFunctor<TReturn(TClass::*)(TArgs...) const>(memberConstFunction, instance);

	m_functor.reset(new LoggableFunctor<TReturn(TArgs...)>("MemberConstFunctionFunctor", unloggableFunctor));
}

template <typename TReturn, typename... TArgs>
TReturn LoggableDelegate<TReturn(TArgs...)>::invoke(TArgs&&... args)
{
	if (!m_functor)
		throw UnboundDelegateException();

	m_functor->operator()(std::forward<TArgs>(args)...);
}

template <typename TReturn, typename... TArgs>
bool LoggableDelegate<TReturn(TArgs...)>::operator==(const LoggableDelegate& delegate)
{
	auto* self = m_functor.get();
	auto* target = delegate.m_functor.get();

	bool areBothEmpty = self == nullptr && target == nullptr;
	bool areBothValid = self != nullptr && target != nullptr;
	bool areBothEqual = areBothValid && (*self == *target);

	return areBothEmpty || areBothEqual;
}

#endif