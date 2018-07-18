template <typename T>
array_view<T>::array_view(pointer d, size_type s) noexcept
	: mData{d}
	, mSize{s}
{}

template <typename T>
template <size_t Size>
array_view<T>::array_view(c_array<T, Size> & array) noexcept
	: mData{array}
	, mSize{Size}
{}

template <typename T>
typename array_view<T>::reference array_view<T>::at(size_type index) const
{
	if (index >= size())
		throw std::out_of_range{};
	return data()[index];
}

template <typename T>
typename array_view<T>::reference array_view<T>::operator [] (size_type index) const noexcept
{
	return data()[index];
}

template <typename T>
typename array_view<T>::reference array_view<T>::front() const noexcept
{
	return *data();
}

template <typename T>
typename array_view<T>::reference array_view<T>::back() const noexcept
{
	return data()[size() - 1];
}

template <typename T>
typename array_view<T>::pointer array_view<T>::data() const noexcept
{
	return mData;
}

template <typename T>
typename array_view<T>::iterator array_view<T>::begin() const noexcept
{
	return data();
}

template <typename T>
typename array_view<T>::const_iterator array_view<T>::cbegin() const noexcept
{
	return data();
}

template <typename T>
typename array_view<T>::iterator array_view<T>::end() const noexcept
{
	return data() + size();
}

template <typename T>
typename array_view<T>::const_iterator array_view<T>::cend() const noexcept
{
	return data() + size();
}

template <typename T>
typename array_view<T>::reverse_iterator array_view<T>::rbegin() const noexcept
{
	return std::reverse_iterator<iterator>{ &back() };
}

template <typename T>
typename array_view<T>::const_reverse_iterator array_view<T>::crbegin() const noexcept
{
	return std::reverse_iterator<iterator>{ &back() };
}

template <typename T>
typename array_view<T>::reverse_iterator array_view<T>::rend() const noexcept
{
	return std::reverse_iterator<iterator>{ data() - 1 };
}

template <typename T>
typename array_view<T>::const_reverse_iterator array_view<T>::crend() const noexcept
{
	return std::reverse_iterator<iterator>{ data() - 1 };
}

template <typename T>
typename array_view<T>::iterator array_view<T>::nth(size_type index) const noexcept
{
	return begin() + index;
}

template <typename T>
bool array_view<T>::empty() const noexcept
{
	return mSize == 0;
}

template <typename T>
typename array_view<T>::size_type array_view<T>::size() const noexcept
{
	return mSize;
}

template <typename T>
typename array_view<T>::size_type array_view<T>::max_size() const noexcept
{
	return size();
}

template <typename T>
void array_view<T>::swap(array_view & other) noexcept
{
	std::swap(mSize, other.mSize);
	std::swap(mData, other.mData);
}

template <typename T>
inline bool operator == (const array_view<T> & a, const array_view<T> & b) noexcept
{
	return (a.size() == b.size()) &&
		std::equal(a.begin(), a.end(), b.begin(), b.end());
}

template <typename T>
inline bool operator != (const array_view<T> & a, const array_view<T> & b) noexcept
{
	return !(a == b);
}

template <typename T>
inline bool operator < (const array_view<T> & a, const array_view<T> & b) noexcept
{
	return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end(), std::less<T>{});
}

template <typename T>
inline bool operator <= (const array_view<T> & a, const array_view<T> & b) noexcept
{
	return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end(), std::less_equal<T>{});
}

template <typename T>
inline bool operator > (const array_view<T> & a, const array_view<T> & b) noexcept
{
	return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end(), std::greater<T>{});
}

template <typename T>
inline bool operator >= (const array_view<T> & a, const array_view<T> & b) noexcept
{
	return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end(), std::greater_equal<T>{});
}

namespace std
{

	template <typename T>
	void swap(const array_view<T> & a, const array_view<T> & b) noexcept
	{
		a.swap(b);
	}

}
