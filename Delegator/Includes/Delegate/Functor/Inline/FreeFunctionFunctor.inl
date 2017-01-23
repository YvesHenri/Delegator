template <typename TReturn, typename... TArgs>
FreeFunctionFunctor<TReturn(TArgs...)>::FreeFunctionFunctor(const FreeFunction function)
	: m_function(function)
{}

//template <typename TReturn, typename... TArgs>
//bool FreeFunctionFunctor<TReturn(TArgs...)>::operator==(const Functor<TReturn(TArgs...)>& functor)
//{
//	return true;
//}

template <typename TReturn, typename... TArgs>
TReturn FreeFunctionFunctor<TReturn(TArgs...)>::operator()(TArgs&&... args)
{
	if (m_function == nullptr)
		throw UnboundDelegateException();

	return m_function(std::forward<TArgs>(args)...);
}