template <typename T>
compressed_pair_base_non_empty<T>::compressed_pair_base_non_empty(const T & x)
	: first_element(x)
{}

template <typename T>
compressed_pair_base_non_empty<T>::compressed_pair_base_non_empty(T && x)
	: first_element(std::move(x))
{}

template <typename T>
template <typename U>
compressed_pair_base_non_empty<T>::compressed_pair_base_non_empty(U && x)
	: first_element(std::forward<U>(x))
{}

template <typename T>
T & compressed_pair_base_non_empty<T>::first() noexcept
{
	return first_element;
}

template <typename T>
const T & compressed_pair_base_non_empty<T>::first() const noexcept
{
	return first_element;
}

//**************************************************************************************************

template <typename T>
compressed_pair_base_empty<T>::compressed_pair_base_empty(const T & x)
	: T(x)
{}

template <typename T>
compressed_pair_base_empty<T>::compressed_pair_base_empty(T && x)
	: T(std::move(x))
{}

template <typename T>
template <typename U>
compressed_pair_base_empty<T>::compressed_pair_base_empty(U && x)
	: T(std::forward<U>(x))
{}

template <typename T>
T & compressed_pair_base_empty<T>::first() noexcept
{
	return static_cast<T &>(*this);
}

template <typename T>
const T & compressed_pair_base_empty<T>::first() const noexcept
{
	return static_cast<const T &>(*this);
}

//**************************************************************************************************

template <typename T1, typename T2>
compressed_pair<T1, T2>::compressed_pair(const T1 & x, const T2 & y)
	: compressed_pair_base<T1>(x)
	, second_element(y)
{}

template <typename T1, typename T2>
template <typename U1, typename U2, typename, typename>
compressed_pair<T1, T2>::compressed_pair(U1 && x, U2 && y)
	: compressed_pair_base<T1>(std::forward<U1>(x))
	, second_element(std::forward<U2>(y))
{}

template <typename T1, typename T2>
template <typename U1, typename U2, typename, typename>
compressed_pair<T1, T2>::compressed_pair(const compressed_pair<U1, U2> & other)
	: compressed_pair_base<T1>(other.first())
	, second_element(other.second())
{}

template <typename T1, typename T2>
template <typename U1, typename U2, typename, typename>
compressed_pair<T1, T2>::compressed_pair(compressed_pair<U1, U2> && other)
	: compressed_pair_base<T1>(std::move(other.first()))
	, second_element(std::move(other.second()))
{}

template <typename T1, typename T2>
template <typename U1, typename U2>
compressed_pair<T1, T2> & compressed_pair<T1, T2>::operator = (const compressed_pair<U1, U2> & other)
{
	first() = other.first();
	second() = other.second();
	return *this;
}

template <typename T1, typename T2>
template <typename U1, typename U2>
compressed_pair<T1, T2> & compressed_pair<T1, T2>::operator = (compressed_pair<U1, U2> && other)
{
	first() = std::move(other.first());
	second() = std::move(other.second());
	return *this;
}

template <typename T1, typename T2>
T2 & compressed_pair<T1, T2>::second() noexcept
{
	return second_element;
}

template <typename T1, typename T2>
const T2 & compressed_pair<T1, T2>::second() const noexcept
{
	return second_element;
}
