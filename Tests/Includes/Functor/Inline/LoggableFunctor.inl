#ifndef LOGGABLE_FUNCTOR_IMPL
#define LOGGABLE_FUNCTOR_IMPL

template <typename TReturn, typename... TArgs>
LoggableFunctor<TReturn(TArgs...)>::LoggableFunctor(std::string label, Functor<TReturn(TArgs...)>* unloggableFunctor)
	: m_label(label)
	, m_unloggableFunctor(unloggableFunctor)
{
	printf("[LOG] +++ %s::Constructor @ %p +++\n", m_label.c_str(), this);
}

template <typename TReturn, typename... TArgs>
LoggableFunctor<TReturn(TArgs...)>::~LoggableFunctor()
{
	printf("[LOG] --- %s::Destructor @ %p ---\n", m_label.c_str(), this);
}

template <typename TReturn, typename... TArgs>
bool LoggableFunctor<TReturn(TArgs...)>::operator==(const LoggableFunctor<TReturn(TArgs...)>& loggableFunctor)
{
	printf("[LOG] %s::operator== @ %p \n", m_label.c_str(), this);
	
	return m_unloggableFunctor->operator==(*loggableFunctor.m_unloggableFunctor);
}

template <typename TReturn, typename... TArgs>
TReturn LoggableFunctor<TReturn(TArgs...)>::operator()(TArgs&&... args)
{
	printf("[LOG] %s::operator() @ %p \n", m_label.c_str(), this);

	return m_unloggableFunctor->operator()(std::forward<TArgs>(args)...);
}

#endif