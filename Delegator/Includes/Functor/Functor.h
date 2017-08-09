#ifndef FUNCTOR_H
#define FUNCTOR_H

// Non specialized template declaration for a functor (empty)
template <typename>
class Functor;

// Specialization for a functor
template <typename TReturn, typename... TArgs>
class Functor<TReturn(TArgs...)>
{
public:
	virtual ~Functor() = default;

	// Checks whether both functors point to the same function
	virtual bool operator==(const Functor<TReturn(TArgs...)>& functor) = 0;

	// Executes the internally stored function
	virtual TReturn operator()(TArgs&&... args) = 0;
};

#endif