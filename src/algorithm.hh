#pragma once

//! Moves all the elements in the range [first, last) one position forward such that
//! the range (first, last] becomes a valid range afterwards and contains the contents
//! previously in [first, last). The contents of *first are undefined after calling this function
template <typename BidirectionalIterator>
void push_forward(BidirectionalIterator first, BidirectionalIterator last);

//! Removes the elements in the range [first, last) from the array [first, range_end) by moving them to the end and invoking the destructor on them
//! Returns an iterator to the new end of the array
template <typename ForwardIterator>
ForwardIterator erase(ForwardIterator first, ForwardIterator last, ForwardIterator range_end);

//! Applies the given function to the elements in the range [first1, last1) and constructs
//! elements in the range [d_first, d_first + (last1 - first1)) from the return values.
//! Returns the end iterator of the output range
template<typename InputIterator, typename OutputIterator, typename UnaryOperation>
OutputIterator uninitialized_transform(InputIterator first1, InputIterator last1, OutputIterator d_first, UnaryOperation unary_op);

//! Applies the given function to the elements in the range [first1, last1) and the elements in the range starting
//! at first2 and constructs elements in the range [d_first, d_first + (last1 - first1)) from the return values.
//! Returns the end iterator of the output range
template <typename InputIterator1, typename InputIterator2, typename OutputIterator, typename BinaryOperation>
OutputIterator uninitialized_transform(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, OutputIterator d_first, BinaryOperation binary_op);

namespace std
{
	// Copied from cppreference because for some reason this is C++17
	template <typename InputIterator, typename ForwardIterator>
	ForwardIterator uninitialized_move(InputIterator first, InputIterator last, ForwardIterator d_first);

	template <typename T>
	void destroy_at(T * p);

	template <typename ForwardIterator>
	void destroy(ForwardIterator first, ForwardIterator last);

}

#include "algorithm.inl"
