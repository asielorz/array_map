#pragma once

#include <iterator> // reverse_iterator
#include <algorithm> // fill, lexicographical_compare, swap
#include <functional> // equal_to, less, less_equal, greater, greater_equal

template <typename T, size_t N>
using c_array = T[N];

template <typename T>
class array_view
{
public:
	using value_type = T;
	using size_type = std::size_t;
	using difference_type = std::ptrdiff_t;
	using reference = value_type &;
	using const_reference = const value_type &;
	using pointer = value_type *;
	using const_pointer = const value_type *;
	using iterator = pointer;
	using const_iterator = const_pointer;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

	array_view() noexcept = default;
	array_view(pointer data, size_type size) noexcept;

	template <size_t Size>
	array_view(c_array<T, Size> & array) noexcept;

	reference at(size_type index) const;

	reference operator [] (size_type index) const noexcept;

	reference front() const noexcept;

	reference back() const noexcept;

	pointer data() const noexcept;

	iterator begin() const noexcept;
	const_iterator cbegin() const noexcept;

	iterator end() const noexcept;
	const_iterator cend() const noexcept;

	reverse_iterator rbegin() const noexcept;
	const_reverse_iterator crbegin() const noexcept;

	reverse_iterator rend() const noexcept;
	const_reverse_iterator crend() const noexcept;

	iterator nth(size_type index) const noexcept;

	bool empty() const noexcept;
	size_type size() const noexcept;
	size_type max_size() const noexcept;

	void swap(array_view & other) noexcept;

private:
	pointer mData = nullptr;
	size_type mSize = 0;
};


template <typename T>
inline bool operator == (const array_view<T> & a, const array_view<T> & b) noexcept;
template <typename T>
inline bool operator != (const array_view<T> & a, const array_view<T> & b) noexcept;
template <typename T>
inline bool operator < (const array_view<T> & a, const array_view<T> & b) noexcept;
template <typename T>
inline bool operator <= (const array_view<T> & a, const array_view<T> & b) noexcept;
template <typename T>
inline bool operator > (const array_view<T> & a, const array_view<T> & b) noexcept;
template <typename T>
inline bool operator >= (const array_view<T> & a, const array_view<T> & b) noexcept;


namespace std
{
	template <typename T>
	void swap(const array_view<T> & a, const array_view<T> & b) noexcept;
}

#include "array_view.inl"
