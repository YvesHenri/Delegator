#ifndef MEMBER_CONST_FUNCTION_FUNCTOR_IMPL
#define MEMBER_CONST_FUNCTION_FUNCTOR_IMPL

namespace fn
{
	template <class TClass, typename TReturn, typename... TArgs>
	MemberConstFunctionFunctor<TReturn(TClass::*)(TArgs...) const>::MemberConstFunctionFunctor(const MemberConstFunction function, const MemberConstInstance instance)
		: m_function(function)
		, m_instance(instance)
	{}

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
		if (m_function == nullptr)
			throw std::exception("Unbound delegate");
		if (m_instance == nullptr)
			throw std::exception("Invalid member instance");

		return (m_instance->*m_function)(std::forward<TArgs>(args)...);
	}
}

#endif