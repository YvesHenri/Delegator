#ifndef MEMBER_FUNCTION_FUNCTOR_IMPL
#define MEMBER_FUNCTION_FUNCTOR_IMPL

template <class TClass, typename TReturn, typename... TArgs>
MemberFunctionFunctor<TReturn(TClass::*)(TArgs...)>::MemberFunctionFunctor(const MemberFunction function, const MemberInstance instance)
	: m_function(function)
	, m_instance(instance)
{}

template <class TClass, typename TReturn, typename... TArgs>
bool MemberFunctionFunctor<TReturn(TClass::*)(TArgs...)>::operator!()
{
	return m_function == nullptr || m_instance == nullptr;
}

//template <class TClass, typename TReturn, typename... TArgs>
//bool MemberFunctionFunctor<TReturn(TClass::*)(TArgs...)>::operator==(const Functor<TReturn(TArgs...)>& functor)
//{
//	return true;
//}

template <class TClass, typename TReturn, typename... TArgs>
TReturn MemberFunctionFunctor<TReturn(TClass::*)(TArgs...)>::operator()(TArgs&&... args)
{
	if (m_function == nullptr || m_instance == nullptr)
		throw UnboundDelegateException();

	return (m_instance->*m_function)(std::forward<TArgs>(args)...);
}

#endif