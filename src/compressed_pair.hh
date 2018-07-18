#pragma once

#include <type_traits>

template <typename T>
struct compressed_pair_base_non_empty
{
	compressed_pair_base_non_empty() = default;
	compressed_pair_base_non_empty(const compressed_pair_base_non_empty &) = default;
	compressed_pair_base_non_empty(compressed_pair_base_non_empty &&) = default;

	compressed_pair_base_non_empty(const T & x);
	compressed_pair_base_non_empty(T && x);

	template <typename U>
	compressed_pair_base_non_empty(U && x);

	T & first() noexcept;
	const T & first() const noexcept;

private:
	T first_element;
};

template <typename T>
struct compressed_pair_base_empty : private T
{
	compressed_pair_base_empty() = default;
	compressed_pair_base_empty(const compressed_pair_base_empty &) = default;
	compressed_pair_base_empty(compressed_pair_base_empty &&) = default;

	compressed_pair_base_empty(const T & x);
	compressed_pair_base_empty(T && x);

	template <typename U>
	compressed_pair_base_empty(U && x);

	T & first() noexcept;
	const T & first() const noexcept;
};

template <typename T>
using compressed_pair_base = std::conditional_t<std::is_empty<T>::value,
	compressed_pair_base_empty<T>,
	compressed_pair_base_non_empty<T>>;

template <typename T1, typename T2>
struct compressed_pair : compressed_pair_base<T1>
{
	compressed_pair() = default;
	compressed_pair(const T1 & x, const T2 & y);

	template <typename U1, typename U2,
		typename = std::enable_if_t<std::is_constructible<T1, U1 &&>::value>,
		typename = std::enable_if_t<std::is_constructible<T2, U2 &&>::value>>
	compressed_pair(U1 && x, U2 && y);

	template <typename U1, typename U2,
		typename = std::enable_if_t<std::is_constructible<T1, const U1 &>::value>,
		typename = std::enable_if_t<std::is_constructible<T2, const U2 &>::value>>
	compressed_pair(const compressed_pair<U1, U2> & other);

	template <typename U1, typename U2,
		typename = std::enable_if_t<std::is_constructible<T1, U1 &&>::value>,
		typename = std::enable_if_t<std::is_constructible<T2, U2 &&>::value>>
	compressed_pair(compressed_pair<U1, U2> && other);

	compressed_pair(const compressed_pair &) = default;
	compressed_pair(compressed_pair &&) = default;

	compressed_pair & operator = (const compressed_pair &) = default;
	compressed_pair & operator = (compressed_pair &&) = default;

	template <typename U1, typename U2>
	compressed_pair & operator = (const compressed_pair<U1, U2> & other);

	template <typename U1, typename U2>
	compressed_pair & operator = (compressed_pair<U1, U2> && other);

	T2 & second() noexcept;
	const T2 & second() const noexcept;

private:
	T2 second_element;
};

#include "compressed_pair.inl"
