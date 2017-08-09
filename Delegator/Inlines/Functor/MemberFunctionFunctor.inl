#ifndef MEMBER_FUNCTION_FUNCTOR_IMPL
#define MEMBER_FUNCTION_FUNCTOR_IMPL

template <class TClass, typename TReturn, typename... TArgs>
MemberFunctionFunctor<TReturn(TClass::*)(TArgs...)>::MemberFunctionFunctor(const MemberFunction function, const MemberInstance instance)
	: m_function(function)
	, m_instance(instance)
{}

template <class TClass, typename TReturn, typename... TArgs>
bool MemberFunctionFunctor<TReturn(TClass::*)(TArgs...)>::operator==(const Functor<TReturn(TArgs...)>& functor)
{
	try
	{
		const MemberFunctionFunctor& member = dynamic_cast<const MemberFunctionFunctor&>(functor);

		return m_function == member.m_function && m_instance == member.m_instance;
	}
	catch (const std::bad_cast&)
	{
		return false;
	}
}

template <class TClass, typename TReturn, typename... TArgs>
TReturn MemberFunctionFunctor<TReturn(TClass::*)(TArgs...)>::operator()(TArgs&&... args)
{
	if (m_function == nullptr)
		throw std::exception("Unbound delegate");
	if (m_instance == nullptr)
		throw std::exception("Invalid member instance");

	return (m_instance->*m_function)(std::forward<TArgs>(args)...);
}

#endif