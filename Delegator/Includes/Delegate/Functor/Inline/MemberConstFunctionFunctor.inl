#ifndef MEMBER_CONST_FUNCTION_FUNCTOR_IMPL
#define MEMBER_CONST_FUNCTION_FUNCTOR_IMPL

template <class TClass, typename TReturn, typename... TArgs>
MemberConstFunctionFunctor<TReturn(TClass::*)(TArgs...) const>::MemberConstFunctionFunctor(const MemberConstFunction function, const MemberConstInstance instance)
	: m_function(function)
	, m_instance(instance)
{
	printf("+++ MemberConstFunctionFunctor +++\n");
}

template <class TClass, typename TReturn, typename... TArgs>
MemberConstFunctionFunctor<TReturn(TClass::*)(TArgs...) const>::~MemberConstFunctionFunctor()
{
	printf("--- MemberConstFunctionFunctor ---\n");
}

template <class TClass, typename TReturn, typename... TArgs>
bool MemberConstFunctionFunctor<TReturn(TClass::*)(TArgs...) const>::operator==(const Functor<TReturn(TArgs...)>& functor)
{
	try
	{
		const MemberConstFunctionFunctor& memberConst = dynamic_cast<const MemberConstFunctionFunctor&>(functor);

		return m_function == memberConst.m_function && m_instance == memberConst.m_instance;
	}
	catch (const std::bad_cast&)
	{
		return false;
	}
}

template <class TClass, typename TReturn, typename... TArgs>
TReturn MemberConstFunctionFunctor<TReturn(TClass::*)(TArgs...) const>::operator()(TArgs&&... args)
{
	if (m_function == nullptr || m_instance == nullptr)
		throw UnboundDelegateException();

	return (m_instance->*m_function)(std::forward<TArgs>(args)...);
}

#endif