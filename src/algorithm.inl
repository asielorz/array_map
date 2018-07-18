template <typename BidirectionalIterator>
void push_forward(BidirectionalIterator first, BidirectionalIterator last)
{
	using value_t = typename std::iterator_traits<BidirectionalIterator>::value_type;
	for (auto it = last; it != first; --it)
		::new(std::addressof(*it)) value_t(std::move(*(std::prev(it))));
}

template <typename ForwardIterator>
ForwardIterator erase(ForwardIterator first, ForwardIterator last, ForwardIterator range_end)
{
	const ForwardIterator new_end = std::rotate(first, last, range_end);
	std::destroy(new_end, range_end);
	return new_end;
}

template <typename InputIterator, typename OutputIterator, typename UnaryOperation>
OutputIterator uninitialized_transform(InputIterator first1, InputIterator last1, OutputIterator d_first, UnaryOperation unary_op)
{
	using out_t = typename std::iterator_traits<OutputIterator>::value_type;

	while (first1 != last1)
		::new (std::addressof(*d_first++)) out_t(unary_op(*first1++));

	return d_first;
}

template <typename InputIterator1, typename InputIterator2, typename OutputIterator, typename BinaryOperation>
OutputIterator uninitialized_transform(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, OutputIterator d_first, BinaryOperation binary_op)
{
	using out_t = typename std::iterator_traits<OutputIterator>::value_type;

	while (first1 != last1)
		::new (std::addressof(*d_first++)) out_t(binary_op(*first1++, *first2++));

	return d_first;
}

namespace std
{
	// Copied from cppreference because for some reason this is C++17
	template <typename InputIterator, typename ForwardIterator>
	ForwardIterator uninitialized_move(InputIterator first, InputIterator last, ForwardIterator d_first)
	{
		for (; first != last; ++d_first, (void) ++first)
			::new (static_cast<void*>(std::addressof(*d_first)))
			typename std::iterator_traits<ForwardIterator>::value_type(std::move(*first));
		return d_first;
	}

	template <typename T>
	void destroy_at(T * p)
	{
		static_cast<void>(p);
		p->~T();
	}

	template <typename ForwardIterator>
	void destroy(ForwardIterator first, ForwardIterator last)
	{
		for (; first != last; ++first)
			std::destroy_at(std::addressof(*first));
	}
}
