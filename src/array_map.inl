namespace iterators
{

	template <typename Key, typename T, class Compare, class Allocator>
	array_map_iterator<Key, T, Compare, Allocator>::array_map_iterator(array_map<Key, T, Compare, Allocator> * t, ptrdiff_t i) noexcept
		: mMap(t), mIndex(i)
	{}

	template <typename Key, typename T, class Compare, class Allocator>
	array_map_iterator<Key, T, Compare, Allocator> & array_map_iterator<Key, T, Compare, Allocator>::operator ++ () noexcept
	{
		++mIndex;
		return *this;
	}

	template <typename Key, typename T, class Compare, class Allocator>
	array_map_iterator<Key, T, Compare, Allocator> array_map_iterator<Key, T, Compare, Allocator>::operator ++ (int) noexcept
	{
		const auto temp = *this;
		++mIndex;
		return temp;
	}

	template <typename Key, typename T, class Compare, class Allocator>
	array_map_iterator<Key, T, Compare, Allocator> & array_map_iterator<Key, T, Compare, Allocator>::operator -- () noexcept
	{
		--mIndex;
		return *this;
	}

	template <typename Key, typename T, class Compare, class Allocator>
	array_map_iterator<Key, T, Compare, Allocator> array_map_iterator<Key, T, Compare, Allocator>::operator -- (int) noexcept
	{
		const auto temp = *this;
		--mIndex;
		return temp;
	}

	template <typename Key, typename T, class Compare, class Allocator>
	array_map_iterator<Key, T, Compare, Allocator> array_map_iterator<Key, T, Compare, Allocator>::operator + (ptrdiff_t n) const noexcept
	{
		auto temp = *this;
		temp += n;
		return temp;
	}

	template <typename Key, typename T, class Compare, class Allocator>
	array_map_iterator<Key, T, Compare, Allocator> operator + (ptrdiff_t n, const array_map_iterator<Key, T, Compare, Allocator> & it) noexcept
	{
		return it + n;
	}

	template <typename Key, typename T, class Compare, class Allocator>
	array_map_iterator<Key, T, Compare, Allocator> array_map_iterator<Key, T, Compare, Allocator>::operator - (ptrdiff_t n) const noexcept
	{
		return (*this) + (-n);
	}

	template <typename Key, typename T, class Compare, class Allocator>
	array_map_iterator<Key, T, Compare, Allocator> & array_map_iterator<Key, T, Compare, Allocator>::operator += (ptrdiff_t n) noexcept
	{
		mIndex += n;
		return *this;
	}

	template <typename Key, typename T, class Compare, class Allocator>
	array_map_iterator<Key, T, Compare, Allocator> & array_map_iterator<Key, T, Compare, Allocator>::operator -= (ptrdiff_t n) noexcept
	{
		mIndex -= n;
		return *this;
	}

	template <typename Key, typename T, class Compare, class Allocator>
	ptrdiff_t array_map_iterator<Key, T, Compare, Allocator>::operator - (const array_map_iterator & other) const noexcept
	{
		return mIndex - other.mIndex;
	}

	template <typename Key, typename T, class Compare, class Allocator>
	typename array_map_iterator<Key, T, Compare, Allocator>::value_type array_map_iterator<Key, T, Compare, Allocator>::operator * () const noexcept
	{
		return { mMap->key_at(index()), mMap->value_at(index()) };
	}

	template <typename Key, typename T, class Compare, class Allocator>
	iterator_arrow_t<Key, T> array_map_iterator<Key, T, Compare, Allocator>::operator -> () const noexcept
	{
		return iterator_arrow_t<Key, T>(**this);
	}

	template <typename Key, typename T, class Compare, class Allocator>
	bool array_map_iterator<Key, T, Compare, Allocator>::operator == (const array_map_iterator & other) const noexcept
	{
		return mMap == other.mMap && mIndex == other.mIndex;
	}

	template <typename Key, typename T, class Compare, class Allocator>
	bool array_map_iterator<Key, T, Compare, Allocator>::operator != (const array_map_iterator & other) const noexcept
	{
		return !(*this == other);
	}

	template <typename Key, typename T, class Compare, class Allocator>
	bool array_map_iterator<Key, T, Compare, Allocator>::operator < (const array_map_iterator & other) const noexcept
	{
		return mIndex < other.mIndex;
	}

	template <typename Key, typename T, class Compare, class Allocator>
	bool array_map_iterator<Key, T, Compare, Allocator>::operator <= (const array_map_iterator & other) const noexcept
	{
		return mIndex <= other.mIndex;
	}

	template <typename Key, typename T, class Compare, class Allocator>
	bool array_map_iterator<Key, T, Compare, Allocator>::operator > (const array_map_iterator & other) const noexcept
	{
		return mIndex > other.mIndex;
	}

	template <typename Key, typename T, class Compare, class Allocator>
	bool array_map_iterator<Key, T, Compare, Allocator>::operator >= (const array_map_iterator & other) const noexcept
	{
		return mIndex >= other.mIndex;
	}

	template <typename Key, typename T, class Compare, class Allocator>
	size_t array_map_iterator<Key, T, Compare, Allocator>::index() const noexcept
	{
		return static_cast<size_t>(mIndex);
	}

	template <typename Key, typename T, class Compare, class Allocator>
	array_map<Key, T, Compare, Allocator> * array_map_iterator<Key, T, Compare, Allocator>::map() const noexcept
	{
		return mMap;
	}

	//*********************************************************************************************************************

	template <typename Key, typename T, class Compare, class Allocator>
	array_map_const_iterator<Key, T, Compare, Allocator>::array_map_const_iterator(const array_map<Key, T, Compare, Allocator> * t, ptrdiff_t i) noexcept
		: mMap(t), mIndex(i)
	{}

	template <typename Key, typename T, class Compare, class Allocator>
	array_map_const_iterator<Key, T, Compare, Allocator>::array_map_const_iterator(const array_map_iterator<Key, T, Compare, Allocator> & it) noexcept
		: mMap(it.mMap), mIndex(it.mIndex)
	{}

	template <typename Key, typename T, class Compare, class Allocator>
	array_map_const_iterator<Key, T, Compare, Allocator> & array_map_const_iterator<Key, T, Compare, Allocator>::operator ++ () noexcept
	{
		++mIndex;
		return *this;
	}

	template <typename Key, typename T, class Compare, class Allocator>
	array_map_const_iterator<Key, T, Compare, Allocator> array_map_const_iterator<Key, T, Compare, Allocator>::operator ++ (int) noexcept
	{
		const auto temp = *this;
		++mIndex;
		return temp;
	}

	template <typename Key, typename T, class Compare, class Allocator>
	array_map_const_iterator<Key, T, Compare, Allocator> & array_map_const_iterator<Key, T, Compare, Allocator>::operator -- () noexcept
	{
		--mIndex;
		return *this;
	}

	template <typename Key, typename T, class Compare, class Allocator>
	array_map_const_iterator<Key, T, Compare, Allocator> array_map_const_iterator<Key, T, Compare, Allocator>::operator -- (int) noexcept
	{
		const auto temp = *this;
		--mIndex;
		return temp;
	}

	template <typename Key, typename T, class Compare, class Allocator>
	array_map_const_iterator<Key, T, Compare, Allocator> array_map_const_iterator<Key, T, Compare, Allocator>::operator + (ptrdiff_t n) const noexcept
	{
		auto temp = *this;
		temp += n;
		return temp;
	}

	template <typename Key, typename T, class Compare, class Allocator>
	array_map_const_iterator<Key, T, Compare, Allocator> operator + (ptrdiff_t n, const array_map_const_iterator<Key, T, Compare, Allocator> & it) noexcept
	{
		return it + n;
	}

	template <typename Key, typename T, class Compare, class Allocator>
	array_map_const_iterator<Key, T, Compare, Allocator> array_map_const_iterator<Key, T, Compare, Allocator>::operator - (ptrdiff_t n) const noexcept
	{
		return (*this) + (-n);
	}

	template <typename Key, typename T, class Compare, class Allocator>
	array_map_const_iterator<Key, T, Compare, Allocator> & array_map_const_iterator<Key, T, Compare, Allocator>::operator += (ptrdiff_t n) noexcept
	{
		mIndex += n;
		return *this;
	}

	template <typename Key, typename T, class Compare, class Allocator>
	array_map_const_iterator<Key, T, Compare, Allocator> & array_map_const_iterator<Key, T, Compare, Allocator>::operator -= (ptrdiff_t n) noexcept
	{
		mIndex -= n;
		return *this;
	}

	template <typename Key, typename T, class Compare, class Allocator>
	ptrdiff_t array_map_const_iterator<Key, T, Compare, Allocator>::operator - (const array_map_const_iterator & other) const noexcept
	{
		return mIndex - other.mIndex;
	}

	template <typename Key, typename T, class Compare, class Allocator>
	typename array_map_const_iterator<Key, T, Compare, Allocator>::value_type array_map_const_iterator<Key, T, Compare, Allocator>::operator * () const noexcept
	{
		return{ mMap->key_at(index()), mMap->value_at(index()) };
	}

	template <typename Key, typename T, class Compare, class Allocator>
	typename array_map_const_iterator<Key, T, Compare, Allocator>::pointer array_map_const_iterator<Key, T, Compare, Allocator>::operator -> () const noexcept
	{
		return pointer(**this);
	}

	template <typename Key, typename T, class Compare, class Allocator>
	bool array_map_const_iterator<Key, T, Compare, Allocator>::operator == (const array_map_const_iterator & other) const noexcept
	{
		return mMap == other.mMap && mIndex == other.mIndex;
	}

	template <typename Key, typename T, class Compare, class Allocator>
	bool array_map_const_iterator<Key, T, Compare, Allocator>::operator != (const array_map_const_iterator & other) const noexcept
	{
		return !(*this == other);
	}

	template <typename Key, typename T, class Compare, class Allocator>
	bool array_map_const_iterator<Key, T, Compare, Allocator>::operator < (const array_map_const_iterator & other) const noexcept
	{
		return mIndex < other.mIndex;
	}

	template <typename Key, typename T, class Compare, class Allocator>
	bool array_map_const_iterator<Key, T, Compare, Allocator>::operator <= (const array_map_const_iterator & other) const noexcept
	{
		return mIndex <= other.mIndex;
	}

	template <typename Key, typename T, class Compare, class Allocator>
	bool array_map_const_iterator<Key, T, Compare, Allocator>::operator > (const array_map_const_iterator & other) const noexcept
	{
		return mIndex > other.mIndex;
	}

	template <typename Key, typename T, class Compare, class Allocator>
	bool array_map_const_iterator<Key, T, Compare, Allocator>::operator >= (const array_map_const_iterator & other) const noexcept
	{
		return mIndex >= other.mIndex;
	}

	template <typename Key, typename T, class Compare, class Allocator>
	size_t array_map_const_iterator<Key, T, Compare, Allocator>::index() const noexcept
	{
		return static_cast<size_t>(mIndex);
	}

	template <typename Key, typename T, class Compare, class Allocator>
	const array_map<Key, T, Compare, Allocator> * array_map_const_iterator<Key, T, Compare, Allocator>::map() const noexcept
	{
		return mMap;
	}

}

template <typename Key, typename T, typename Compare, typename Allocator>
array_map<Key, T, Compare, Allocator>::array_map(const Compare & comp, const Allocator & alloc)
	: Compare(comp)
	, mAllocatorAndCapacity(alloc, 0)
{}

template <typename Key, typename T, typename Compare, typename Allocator>
array_map<Key, T, Compare, Allocator>::array_map(const Allocator & alloc)
	: mAllocatorAndCapacity(alloc, 0)
{}

template <typename Key, typename T, typename Compare, typename Allocator>
array_map<Key, T, Compare, Allocator>::array_map(std::initializer_list<std::pair<Key, T>> ilist, const Compare & comp, const Allocator & alloc)
	: Compare(comp)
	, mAllocatorAndCapacity(alloc, 0)
{
	reserve(ilist.size());
	for (const auto & pair : ilist)
		insert_hint(end(), pair.first, pair.second);
}

template <typename Key, typename T, typename Compare, typename Allocator>
array_map<Key, T, Compare, Allocator>::array_map(ordered_unique_range_t, std::initializer_list<std::pair<Key, T>> ilist, const Compare & comp, const Allocator & alloc)
	: Compare(comp)
	, mAllocatorAndCapacity(alloc, 0)
{
	// Set capacity to the size of the initializer list, then directly copy all keys and values
	reserve(ilist.size());
	uninitialized_transform(ilist.begin(), ilist.end(), keys_ptr(), [](const std::pair<Key, T> & pair) -> const Key & { return pair.first; });
	uninitialized_transform(ilist.begin(), ilist.end(), values_ptr(), [](const std::pair<Key, T> & pair) -> const T & { return pair.second; });
	mSize = ilist.size();
}

template <typename Key, typename T, typename Compare, typename Allocator>
array_map<Key, T, Compare, Allocator>::array_map(const array_map & other)
	: Compare(other.key_comp())
	, mAllocatorAndCapacity(other.get_allocator(), 0)
{
	mData = copy_other(other, get_stored_allocator());
	mSize = other.size();
	set_capacity(other.size());
}

template <typename Key, typename T, typename Compare, typename Allocator>
array_map<Key, T, Compare, Allocator>::array_map(const array_map & other, const Allocator & alloc)
	: Compare(other.key_comp())
	, mAllocatorAndCapacity(other.get_allocator(), 0)
{
	mData = copy_other(other, get_stored_allocator());
	mSize = other.size();
	set_capacity(other.size());
}

template <typename Key, typename T, typename Compare, typename Allocator>
array_map<Key, T, Compare, Allocator> & array_map<Key, T, Compare, Allocator>::operator = (const array_map & other)
{
	copy_assignment_allocator_propagation_dependant_code(other, allocator_traits::propagate_on_container_copy_assignment());
	return *this;
}

template <typename Key, typename T, typename Compare, typename Allocator>
void array_map<Key, T, Compare, Allocator>::copy_assignment_allocator_propagation_dependant_code(const array_map & other, std::true_type)
{
	// Get what will be the new allocator. We have to free with the old allocator but allocate with the new one
	stored_allocator_type new_alloc = allocator_traits::select_on_container_copy_construction(other.get_stored_allocator());

	get_stored_compare() = other.key_comp();

	// If there's no enough space to fit all the elements of the other vector, resize
	if (other.size() > capacity())
	{
		char * new_data = copy_other(other, new_alloc); // Allocate with the new allocator
		destroy_all_and_free();							// Free with the old allocator
		mData = new_data;
		mSize = other.size();
		set_capacity(other.size());
	}
	// Otherwise just copy to the memory we already have
	else
	{
		destroy_all();

		std::uninitialized_copy(other.keys_ptr(), other.keys_ptr() + other.size(), keys_ptr());
		std::uninitialized_copy(other.values_ptr(), other.values_ptr() + other.size(), values_ptr());

		mSize = other.mSize;
	}

	// Assign the new allocator
	get_stored_allocator() = new_alloc;
}

template <typename Key, typename T, typename Compare, typename Allocator>
void array_map<Key, T, Compare, Allocator>::copy_assignment_allocator_propagation_dependant_code(const array_map & other, std::false_type)
{
	get_stored_compare() = other.key_comp();

	// If there's no enough space to fit all the elements of the other vector, resize
	if (other.size() > capacity())
	{
		char * new_data = copy_other(other, get_stored_allocator());
		destroy_all_and_free();
		mData = new_data;
		mSize = other.size();
		set_capacity(other.size());
	}
	// Otherwise just copy to the memory we already have
	else
	{
		destroy_all();

		std::uninitialized_copy(other.keys_ptr(), other.keys_ptr() + other.size(), keys_ptr());
		std::uninitialized_copy(other.values_ptr(), other.values_ptr() + other.size(), values_ptr());

		mSize = other.mSize;
	}
}

template <typename Key, typename T, typename Compare, typename Allocator>
array_map<Key, T, Compare, Allocator>::array_map(array_map && other) noexcept
	: Compare(std::move(other.get_stored_compare()))
	, mAllocatorAndCapacity(std::move(other.get_stored_allocator()), 0)
{
	move_from_other(std::move(other));
}

template <typename Key, typename T, typename Compare, typename Allocator>
array_map<Key, T, Compare, Allocator>::array_map(array_map && other, const Allocator & alloc) noexcept
	: Compare(std::move(other.get_stored_compare()))
	, mAllocatorAndCapacity(alloc, 0)
{
	if (get_stored_allocator() == other.get_stored_allocator())
		move_from_other(std::move(other));
	else
		move_from_other_without_propagation(std::move(other));
}

template <typename Key, typename T, typename Compare, typename Allocator>
array_map<Key, T, Compare, Allocator> & array_map<Key, T, Compare, Allocator>::operator = (array_map && other) noexcept(move_assignment_is_noexcept)
{
	get_stored_compare() = std::move(other.get_stored_compare());
	move_assignment_allocator_propagation_dependant_code(std::move(other), allocator_traits::propagate_on_container_move_assignment());
	return *this;
}

template <typename Key, typename T, typename Compare, typename Allocator>
void array_map<Key, T, Compare, Allocator>::move_assignment_allocator_propagation_dependant_code(array_map && other, std::true_type) noexcept(move_assignment_is_noexcept)
{
	get_stored_allocator() = std::move(other.get_stored_allocator());
	destroy_all_and_free();
	move_from_other(std::move(other));
}

template <typename Key, typename T, typename Compare, typename Allocator>
void array_map<Key, T, Compare, Allocator>::move_assignment_allocator_propagation_dependant_code(array_map && other, std::false_type) noexcept(move_assignment_is_noexcept)
{
	if (get_stored_allocator() == other.get_stored_allocator())
	{
		destroy_all_and_free();
		move_from_other(std::move(other));
	}
	else
		move_from_other_without_propagation(std::move(other));
}

template <typename Key, typename T, typename Compare, typename Allocator>
array_map<Key, T, Compare, Allocator>::~array_map()
{
	destroy_all_and_free();
}

template <typename Key, typename T, typename Compare, typename Allocator>
void array_map<Key, T, Compare, Allocator>::swap(array_map & other)
{
	swap_allocator_propagation_dependant_code(other, allocator_traits::propagate_on_container_swap());
}

template <typename Key, typename T, typename Compare, typename Allocator>
void array_map<Key, T, Compare, Allocator>::swap_allocator_propagation_dependant_code(array_map & other, std::true_type)
{
	std::swap(get_stored_allocator(), other.get_stored_allocator());
	swap_with_same_allocator(other);
}

template <typename Key, typename T, typename Compare, typename Allocator>
void array_map<Key, T, Compare, Allocator>::swap_allocator_propagation_dependant_code(array_map & other, std::false_type)
{
	if (get_allocator() == other.get_allocator())
		swap_with_same_allocator(other);
	else
		swap_with_different_allocator(other);
}

template <typename Key, typename T, typename Compare, typename Allocator>
bool array_map<Key, T, Compare, Allocator>::empty() const noexcept
{
	return size() == 0;
}

template <typename Key, typename T, typename Compare, typename Allocator>
size_t array_map<Key, T, Compare, Allocator>::size() const noexcept
{
	return mSize;
}

template <typename Key, typename T, typename Compare, typename Allocator>
size_t array_map<Key, T, Compare, Allocator>::capacity() const noexcept
{
	return mAllocatorAndCapacity.second();
}

template <typename Key, typename T, typename Compare, typename Allocator>
array_view<const Key> array_map<Key, T, Compare, Allocator>::keys() const noexcept
{
	return { keys_ptr(), size() };
}

template <typename Key, typename T, typename Compare, typename Allocator>
array_view<T> array_map<Key, T, Compare, Allocator>::values() noexcept
{
	return { values_ptr(), size() };
}

template <typename Key, typename T, typename Compare, typename Allocator>
array_view<const T> array_map<Key, T, Compare, Allocator>::values() const noexcept
{
	return { values_ptr(), size() };
}

template <typename Key, typename T, typename Compare, typename Allocator>
std::pair<typename array_map<Key, T, Compare, Allocator>::iterator, bool> array_map<Key, T, Compare, Allocator>::insert(Key key, T value)
{
	const auto r = insert_new_element(std::move(key), std::move(value));
	return { nth(r.index), r.inserted };
}

template <typename Key, typename T, typename Compare, typename Allocator>
typename array_map<Key, T, Compare, Allocator>::iterator array_map<Key, T, Compare, Allocator>::insert(const_iterator hint, Key key, T value)
{
	assert(hint.map() == this);
	return nth(insert_hint(hint, std::move(key), std::move(value)).index);
}

template <typename Key, typename T, typename Compare, typename Allocator>
template <typename ... Args>
std::pair<typename array_map<Key, T, Compare, Allocator>::iterator, bool> array_map<Key, T, Compare, Allocator>::emplace(Key key, Args && ... value_ctor_args)
{
	const auto r = insert_new_element(std::move(key), std::forward<Args>(value_ctor_args)...);
	return{ nth(r.index), r.inserted };
}

template <typename Key, typename T, typename Compare, typename Allocator>
template <typename ... Args>
typename array_map<Key, T, Compare, Allocator>::iterator array_map<Key, T, Compare, Allocator>::emplace(const_iterator hint, Key key, Args && ... value_ctor_args)
{
	assert(hint.map() == this);
	return nth(insert_hint(hint, std::move(key), std::forward<Args>(value_ctor_args)...).index);
}

template <typename Key, typename T, typename Compare, typename Allocator>
void array_map<Key, T, Compare, Allocator>::clear() noexcept
{
	destroy_all();
	mSize = 0;
}

template <typename Key, typename T, typename Compare, typename Allocator>
void array_map<Key, T, Compare, Allocator>::shrink_to_fit()
{
	if (capacity() > size())
		change_capacity(size());
}

template <typename Key, typename T, typename Compare, typename Allocator>
void array_map<Key, T, Compare, Allocator>::reserve(size_t new_capacity)
{
	if (new_capacity < capacity())
		return;

	change_capacity(new_capacity);
}

template <typename Key, typename T, typename Compare, typename Allocator>
T & array_map<Key, T, Compare, Allocator>::at(const Key & key)
{
	const auto r = find_index_of(key);
	if (r.found)
		return value_at(r.index);
	else
		throw std::out_of_range("Key not found on array_map::at");
}

template <typename Key, typename T, typename Compare, typename Allocator>
const T & array_map<Key, T, Compare, Allocator>::at(const Key & key) const
{
	const auto r = find_index_of(key);
	if (r.found)
		return value_at(r.index);
	else
		throw std::out_of_range("Key not found on array_map::at");
}

template <typename Key, typename T, typename Compare, typename Allocator>
template <typename TKey, typename Comp, typename, typename>
T & array_map<Key, T, Compare, Allocator>::at(const TKey & key)
{
	const auto r = find_index_of(key);
	if (r.found)
		return value_at(r.index);
	else
		throw std::out_of_range("Key not found on array_map::at");
}

template <typename Key, typename T, typename Compare, typename Allocator>
template <typename TKey, typename Comp, typename, typename>
const T & array_map<Key, T, Compare, Allocator>::at(const TKey & key) const
{
	const auto r = find_index_of(key);
	if (r.found)
		return value_at(r.index);
	else
		throw std::out_of_range("Key not found on array_map::at");
}

template <typename Key, typename T, typename Compare, typename Allocator>
T & array_map<Key, T, Compare, Allocator>::operator [] (const Key & key)
{
	const auto r = insert_new_element(key);
	return value_at(r.index);
}

template <typename Key, typename T, typename Compare, typename Allocator>
T & array_map<Key, T, Compare, Allocator>::operator [] (Key && key)
{
	const auto r = insert_new_element(std::move(key));
	return value_at(r.index);
}

template <typename Key, typename T, typename Compare, typename Allocator>
typename array_map<Key, T, Compare, Allocator>::iterator array_map<Key, T, Compare, Allocator>::find(const Key & key) noexcept
{
	const auto r = find_index_of(key);
	if (r.found)
		return nth(r.index);
	else
		return end();
}

template <typename Key, typename T, typename Compare, typename Allocator>
typename array_map<Key, T, Compare, Allocator>::const_iterator array_map<Key, T, Compare, Allocator>::find(const Key & key) const noexcept
{
	const auto r = find_index_of(key);
	if (r.found)
		return nth(r.index);
	else
		return end();
}

template <typename Key, typename T, typename Compare, typename Allocator>
template <typename TKey, typename Comp, typename, typename>
typename array_map<Key, T, Compare, Allocator>::iterator array_map<Key, T, Compare, Allocator>::find(const TKey & key) noexcept
{
	const auto r = find_index_of(key);
	if (r.found)
		return nth(r.index);
	else
		return end();
}

template <typename Key, typename T, typename Compare, typename Allocator>
template <typename TKey, typename Comp, typename, typename>
typename array_map<Key, T, Compare, Allocator>::const_iterator array_map<Key, T, Compare, Allocator>::find(const TKey & key) const noexcept
{
	const auto r = find_index_of(key);
	if (r.found)
		return nth(r.index);
	else
		return end();
}

template <typename Key, typename T, typename Compare, typename Allocator>
typename array_map<Key, T, Compare, Allocator>::iterator array_map<Key, T, Compare, Allocator>::lower_bound(const Key & key) noexcept
{
	return nth(lower_bound_index(key));
}

template <typename Key, typename T, typename Compare, typename Allocator>
typename array_map<Key, T, Compare, Allocator>::const_iterator array_map<Key, T, Compare, Allocator>::lower_bound(const Key & key) const noexcept
{
	return nth(lower_bound_index(key));
}

template <typename Key, typename T, typename Compare, typename Allocator>
template <typename TKey, typename Comp, typename, typename>
typename array_map<Key, T, Compare, Allocator>::iterator array_map<Key, T, Compare, Allocator>::lower_bound(const TKey & key) noexcept
{
	return nth(lower_bound_index(key));
}

template <typename Key, typename T, typename Compare, typename Allocator>
template <typename TKey, typename Comp, typename, typename>
typename array_map<Key, T, Compare, Allocator>::const_iterator array_map<Key, T, Compare, Allocator>::lower_bound(const TKey & key) const noexcept
{
	return nth(lower_bound_index(key));
}

template <typename Key, typename T, typename Compare, typename Allocator>
typename array_map<Key, T, Compare, Allocator>::iterator array_map<Key, T, Compare, Allocator>::upper_bound(const Key & key) noexcept
{
	return nth(upper_bound_index(key));
}

template <typename Key, typename T, typename Compare, typename Allocator>
typename array_map<Key, T, Compare, Allocator>::const_iterator array_map<Key, T, Compare, Allocator>::upper_bound(const Key & key) const noexcept
{
	return nth(upper_bound_index(key));
}

template <typename Key, typename T, typename Compare, typename Allocator>
template <typename TKey, typename Comp, typename, typename>
typename array_map<Key, T, Compare, Allocator>::iterator array_map<Key, T, Compare, Allocator>::upper_bound(const TKey & key) noexcept
{
	return nth(upper_bound_index(key));
}

template <typename Key, typename T, typename Compare, typename Allocator>
template <typename TKey, typename Comp, typename, typename>
typename array_map<Key, T, Compare, Allocator>::const_iterator array_map<Key, T, Compare, Allocator>::upper_bound(const TKey & key) const noexcept
{
	return nth(upper_bound_index(key));
}

template <typename Key, typename T, typename Compare, typename Allocator>
typename array_map<Key, T, Compare, Allocator>::iterator array_map<Key, T, Compare, Allocator>::erase(iterator pos)
{
	const size_t i = pos.index();
	assert(i < size());
	assert(pos.map() == this);
	
	erase_index(i);

	return pos;
}

template <typename Key, typename T, typename Compare, typename Allocator>
typename array_map<Key, T, Compare, Allocator>::iterator array_map<Key, T, Compare, Allocator>::erase(const_iterator first, const_iterator last)
{
	const size_t first_i = first.index();
	const size_t last_i = last.index();
	const size_t n = last_i - first_i;
	assert(first_i < last_i);
	assert(last_i < size());
	assert(first.map() == this);
	assert(last.map() == this);

	::erase(keys_ptr() + first_i, keys_ptr() + last_i, keys_ptr() + size());

	const auto value_array = values_ptr();
	::erase(value_array + first_i, value_array + last_i, value_array + size());

	mSize -= n;

	return nth(first.index());
}

template <typename Key, typename T, typename Compare, typename Allocator>
size_t array_map<Key, T, Compare, Allocator>::erase(const Key & key)
{
	const auto r = find_index_of(key);
	if (r.found)
	{
		erase_index(r.index);
		return 1;
	}
	else
		return false;
}

template <typename Key, typename T, typename Compare, typename Allocator>
template <typename TKey, typename Comp, typename, typename>
size_t array_map<Key, T, Compare, Allocator>::erase(const TKey & key)
{
	const auto r = find_index_of(key);
	if (r.found)
	{
		erase_index(r.index);
		return 1;
	}
	else
		return false;
}

template <typename Key, typename T, typename Compare, typename Allocator>
void array_map<Key, T, Compare, Allocator>::erase_index(size_t i)
{
	::erase(keys_ptr() + i, keys_ptr() + i + 1, keys_ptr() + size());

	const auto value_array = values_ptr();
	::erase(value_array + i, value_array + i + 1, value_array + size());

	mSize--;
}

template <typename Key, typename T, typename Compare, typename Allocator>
typename array_map<Key, T, Compare, Allocator>::iterator array_map<Key, T, Compare, Allocator>::begin() noexcept
{
	return iterator(this, 0);
}

template <typename Key, typename T, typename Compare, typename Allocator>
typename array_map<Key, T, Compare, Allocator>::iterator array_map<Key, T, Compare, Allocator>::end() noexcept
{
	return iterator(this, size());
}

template <typename Key, typename T, typename Compare, typename Allocator>
typename array_map<Key, T, Compare, Allocator>::const_iterator array_map<Key, T, Compare, Allocator>::begin() const noexcept
{
	return cbegin();
}

template <typename Key, typename T, typename Compare, typename Allocator>
typename array_map<Key, T, Compare, Allocator>::const_iterator array_map<Key, T, Compare, Allocator>::end() const noexcept
{
	return cend();
}

template <typename Key, typename T, typename Compare, typename Allocator>
typename array_map<Key, T, Compare, Allocator>::const_iterator array_map<Key, T, Compare, Allocator>::cbegin() const noexcept
{
	return const_iterator(this, 0);
}

template <typename Key, typename T, typename Compare, typename Allocator>
typename array_map<Key, T, Compare, Allocator>::const_iterator array_map<Key, T, Compare, Allocator>::cend() const noexcept
{
	return const_iterator(this, size());
}

template <typename Key, typename T, typename Compare, typename Allocator>
typename array_map<Key, T, Compare, Allocator>::reverse_iterator array_map<Key, T, Compare, Allocator>::rbegin() noexcept
{
	return std::make_reverse_iterator(end());
}

template <typename Key, typename T, typename Compare, typename Allocator>
typename array_map<Key, T, Compare, Allocator>::reverse_iterator array_map<Key, T, Compare, Allocator>::rend() noexcept
{
	return std::make_reverse_iterator(begin());
}

template <typename Key, typename T, typename Compare, typename Allocator>
typename array_map<Key, T, Compare, Allocator>::const_reverse_iterator array_map<Key, T, Compare, Allocator>::rbegin() const noexcept
{
	return crbegin();
}

template <typename Key, typename T, typename Compare, typename Allocator>
typename array_map<Key, T, Compare, Allocator>::const_reverse_iterator array_map<Key, T, Compare, Allocator>::rend() const noexcept
{
	return crend();
}

template <typename Key, typename T, typename Compare, typename Allocator>
typename array_map<Key, T, Compare, Allocator>::const_reverse_iterator array_map<Key, T, Compare, Allocator>::crbegin() const noexcept
{
	return std::make_reverse_iterator(cend());
}

template <typename Key, typename T, typename Compare, typename Allocator>
typename array_map<Key, T, Compare, Allocator>::const_reverse_iterator array_map<Key, T, Compare, Allocator>::crend() const noexcept
{
	return std::make_reverse_iterator(cbegin());
}

template <typename Key, typename T, typename Compare, typename Allocator>
typename array_map<Key, T, Compare, Allocator>::iterator array_map<Key, T, Compare, Allocator>::nth(size_t n) noexcept
{
	return begin() + n;
}

template <typename Key, typename T, typename Compare, typename Allocator>
typename array_map<Key, T, Compare, Allocator>::const_iterator array_map<Key, T, Compare, Allocator>::nth(size_t n) const noexcept
{
	return begin() + n;
}

template <typename Key, typename T, typename Compare, typename Allocator>
Compare array_map<Key, T, Compare, Allocator>::key_comp() const noexcept
{
	return *this;
}

template <typename Key, typename T, typename Compare, typename Allocator>
Allocator array_map<Key, T, Compare, Allocator>::get_allocator() const noexcept
{
	return get_stored_allocator();
}

//***************************************************************************************************************************

template <typename Key, typename T, typename Compare, typename Allocator>
Key * array_map<Key, T, Compare, Allocator>::keys_ptr() noexcept
{
	return reinterpret_cast<Key *>(mData);
}

template <typename Key, typename T, typename Compare, typename Allocator>
const Key * array_map<Key, T, Compare, Allocator>::keys_ptr() const noexcept
{
	return reinterpret_cast<const Key *>(mData);
}

template <typename Key, typename T, typename Compare, typename Allocator>
T * array_map<Key, T, Compare, Allocator>::values_ptr() noexcept
{
	return value_array(keys_ptr(), capacity());
}

template <typename Key, typename T, typename Compare, typename Allocator>
const T * array_map<Key, T, Compare, Allocator>::values_ptr() const noexcept
{
	return value_array(keys_ptr(), capacity());
}

template <typename Key, typename T, typename Compare, typename Allocator>
const Key & array_map<Key, T, Compare, Allocator>::key_at(size_t index) const noexcept
{
	return *(keys_ptr() + index);
}

template <typename Key, typename T, typename Compare, typename Allocator>
T & array_map<Key, T, Compare, Allocator>::value_at(size_t index) noexcept
{
	return *(values_ptr() + index);
}

template <typename Key, typename T, typename Compare, typename Allocator>
const T & array_map<Key, T, Compare, Allocator>::value_at(size_t index) const noexcept
{
	return *(values_ptr() + index);
}

template <typename Key, typename T, typename Compare, typename Allocator>
typename array_map<Key, T, Compare, Allocator>::stored_allocator_type & array_map<Key, T, Compare, Allocator>::get_stored_allocator() noexcept
{
	return mAllocatorAndCapacity.first();
}

template <typename Key, typename T, typename Compare, typename Allocator>
const typename array_map<Key, T, Compare, Allocator>::stored_allocator_type & array_map<Key, T, Compare, Allocator>::get_stored_allocator() const noexcept
{
	return mAllocatorAndCapacity.first();
}

template <typename Key, typename T, typename Compare, typename Allocator>
Compare & array_map<Key, T, Compare, Allocator>::get_stored_compare() noexcept
{
	return *this;
}

template <typename Key, typename T, typename Compare, typename Allocator>
size_t array_map<Key, T, Compare, Allocator>::capacity_to_bytes(size_t capacity)
{
	const size_t key_bytes = capacity * sizeof(Key);
	const size_t padding_bytes = key_bytes % alignof(T); // Padding between keys and values to ensure values are correctly aligned
	const size_t value_bytes = capacity * sizeof(T);

	return key_bytes + padding_bytes + value_bytes;
}

template <typename Key, typename T, typename Compare, typename Allocator>
T * array_map<Key, T, Compare, Allocator>::value_array(void * data, size_t capacity) noexcept
{
	return const_cast<T *>(value_array(static_cast<const void *>(data), capacity));
}

template <typename Key, typename T, typename Compare, typename Allocator>
const T * array_map<Key, T, Compare, Allocator>::value_array(const void * data, size_t capacity) noexcept
{
	const size_t key_bytes = capacity * sizeof(Key);
	const size_t padding_bytes = key_bytes % alignof(T);

	return reinterpret_cast<const T *>(reinterpret_cast<const char *>(data) + key_bytes + padding_bytes);
}

template <typename Key, typename T, typename Compare, typename Allocator>
void array_map<Key, T, Compare, Allocator>::grow()
{
	if (capacity() == 0)
		reserve(1);
	else
		reserve(capacity() * 2);
}

template <typename Key, typename T, typename Compare, typename Allocator>
void array_map<Key, T, Compare, Allocator>::change_capacity(size_t new_capacity)
{
	// Allocate memory for new capacity
	char * new_data = new_capacity > 0 ?
		allocator_traits::allocate(get_stored_allocator(), capacity_to_bytes(new_capacity)) :
		nullptr;
	Key * new_keys = reinterpret_cast<Key *>(new_data);
	T * new_values = value_array(new_data, new_capacity);

	// Move old values to the new array
	std::uninitialized_move(keys_ptr(), keys_ptr() + size(), new_keys);
	std::uninitialized_move(values_ptr(), values_ptr() + size(), new_values);

	// Destroy old keys and values
	std::destroy(keys_ptr(), keys_ptr() + size());
	std::destroy(values_ptr(), values_ptr() + size());

	// Deallocate old array
	allocator_traits::deallocate(get_stored_allocator(), mData, capacity_to_bytes(capacity()));

	// Set new array and capacity
	mData = new_data;
	set_capacity(new_capacity);
}

template <typename Key, typename T, typename Compare, typename Allocator>
template <typename TKey1, typename TKey2>
bool array_map<Key, T, Compare, Allocator>::keys_equal(const TKey1 & a, const TKey2 & b) const noexcept
{
	const auto compare = key_comp();
	return !compare(a, b) && !compare(b, a);
}

template <typename Key, typename T, typename Compare, typename Allocator>
template <typename TKey>
size_t array_map<Key, T, Compare, Allocator>::lower_bound_index(const TKey & key) const noexcept
{
	return std::lower_bound(keys_ptr(), keys_ptr() + size(), key, key_comp()) - keys_ptr();
}

template <typename Key, typename T, typename Compare, typename Allocator>
template <typename TKey>
size_t array_map<Key, T, Compare, Allocator>::upper_bound_index(const TKey & key) const noexcept
{
	return std::upper_bound(keys_ptr(), keys_ptr() + size(), key, key_comp()) - keys_ptr();
}

template <typename Key, typename T, typename Compare, typename Allocator>
template <typename TKey>
typename array_map<Key, T, Compare, Allocator>::find_result array_map<Key, T, Compare, Allocator>::find_index_of(const TKey & key) const noexcept
{
	const size_t index = lower_bound_index(key);
	const bool found = index != size() && keys_equal(key, key_at(index));
	return { index, found };
}

template <typename Key, typename T, typename Compare, typename Allocator>
template <typename ... Args>
typename array_map<Key, T, Compare, Allocator>::insert_result array_map<Key, T, Compare, Allocator>::insert_new_element(Key key, Args && ... args)
{
	// Look for the inserion point
	const auto r = find_index_of(key);

	// If the key is already in the table, don't insert
	if (r.found)
		return { r.index, false };
	else
		return insert_at_position(r.index, std::move(key), std::forward<Args>(args)...);
}

template <typename Key, typename T, typename Compare, typename Allocator>
template <typename ... Args>
typename array_map<Key, T, Compare, Allocator>::insert_result array_map<Key, T, Compare, Allocator>::insert_hint(const_iterator hint, Key key, Args && ... args)
{
	const auto comp = key_comp();
	// If (hint is end or bigger than key) and (hint is first or previous of hint is less than key)
	if ((hint.index() == size() || comp(key, hint->key)) && (hint.index() == 0 || comp((hint - 1)->key, key)))
		return insert_at_position(hint.index(), std::move(key), std::forward<Args>(args)...);
	else
		return insert_new_element(std::move(key), std::forward<Args>(args)...);
}

template <typename Key, typename T, typename Compare, typename Allocator>
template <typename ... Args>
typename array_map<Key, T, Compare, Allocator>::insert_result array_map<Key, T, Compare, Allocator>::insert_at_position(size_t index, Key key, Args && ... args)
{
	if (size() == capacity())
		grow();

	// Move all elements one forward to make place for the new element
	push_forward(keys_ptr() + index, keys_ptr() + size());

	const auto values_begin = values_ptr() + index;
	push_forward(values_begin, values_ptr() + size());

	// Insert new key and value into the array
	::new (keys_ptr() + index) Key(std::move(key));
	::new (values_begin) T(std::forward<Args>(args)...);

	mSize++;

	return{ index, true };
}

template <typename Key, typename T, typename Compare, typename Allocator>
void array_map<Key, T, Compare, Allocator>::destroy_all() noexcept
{
	std::destroy(keys_ptr(), keys_ptr() + size());
	std::destroy(values_ptr(), values_ptr() + size());
}

template <typename Key, typename T, typename Compare, typename Allocator>
void array_map<Key, T, Compare, Allocator>::destroy_all_and_free() noexcept
{
	if (mData)
	{
		destroy_all();
		allocator_traits::deallocate(get_stored_allocator(), mData, capacity_to_bytes(capacity()));
	}
}

template <typename Key, typename T, typename Compare, typename Allocator>
char * array_map<Key, T, Compare, Allocator>::copy_other(const array_map & other, Allocator & alloc)
{
	// Allocate new block of enough size to fit all the memory of the other
	char * new_data = allocator_traits::allocate(alloc, capacity_to_bytes(other.size()));
	try
	{
		// Try to copy all elements from other to the new block
		std::uninitialized_copy(other.keys_ptr(), other.keys_ptr() + other.size(), reinterpret_cast<Key *>(new_data));
		std::uninitialized_copy(other.values_ptr(), other.values_ptr() + other.size(), value_array(new_data, other.size()));
	}
	catch (...)
	{
		// If copying fails deallocate new block of memory to avoid leaking and rethrow
		allocator_traits::deallocate(alloc, new_data, capacity_to_bytes(other.size()));
		throw;
	}

	return new_data;
}

template <typename Key, typename T, typename Compare, typename Allocator>
void array_map<Key, T, Compare, Allocator>::move_from_other(array_map && other) noexcept
{
	mData = other.mData;
	mSize = other.mSize;
	set_capacity(other.capacity());
	other.mData = nullptr;
	other.mSize = 0;
	other.set_capacity(0);
}

template <typename Key, typename T, typename Compare, typename Allocator>
void array_map<Key, T, Compare, Allocator>::move_from_other_without_propagation(array_map && other)
{
	// If we don't have enough storage, allocate more
	if (capacity() < other.size())
	{
		// Allocate new block of enough size to fit all the memory of the other
		char * new_data = allocator_traits::allocate(get_stored_allocator(), capacity_to_bytes(other.size()));
		try
		{
			// Try to move all elements from other to the new block
			std::uninitialized_move(other.keys_ptr(), other.keys_ptr() + other.size(), reinterpret_cast<Key *>(new_data));
			std::uninitialized_move(other.values_ptr(), other.values_ptr() + other.size(), value_array(new_data, other.size()));
		}
		catch (...)
		{
			// If copying fails deallocate new block of memory to avoid leaking and rethrow
			allocator_traits::deallocate(get_stored_allocator(), new_data, capacity_to_bytes(other.size()));
			throw;
		}

		destroy_all_and_free();

		mData = new_data;
		set_capacity(other.size());
	}
	// If we have enough storage, use the one we already have
	else
	{
		// Destroy all of our elements
		destroy_all();

		// Move all elements from other to the new block
		std::uninitialized_move(other.keys_ptr(), other.keys_ptr() + other.size(), keys_ptr());
		std::uninitialized_move(other.values_ptr(), other.values_ptr() + other.size(), values_ptr());
	}

	mSize = other.size();
	other.mSize = 0;
}

template <typename Key, typename T, class Compare, class Allocator>
void array_map<Key, T, Compare, Allocator>::set_capacity(size_t new_capacity) noexcept
{
	mAllocatorAndCapacity.second() = new_capacity;
}

template <typename Key, typename T, class Compare, class Allocator>
void array_map<Key, T, Compare, Allocator>::swap_with_same_allocator(array_map & other)
{
	std::swap(get_stored_compare(), other.get_stored_compare());
	std::swap(mAllocatorAndCapacity.second(), other.mAllocatorAndCapacity.second());
	std::swap(mSize, other.mSize);
	std::swap(mData, other.mData);
}

template <typename Key, typename T, class Compare, class Allocator>
void array_map<Key, T, Compare, Allocator>::swap_with_different_allocator(array_map & other)
{
	array_map & small = size() < other.size() ? *this : other;
	array_map & big = &small == this ? other : *this;

	// Ensure the smallest of the maps has enough capacity to fit the elements of the big one
	small.reserve(big.size());

	// Swap the first n keys where n is the size of the smallest of the maps
	std::swap_ranges(small.keys_ptr(), small.keys_ptr() + small.size(), big.keys_ptr());
	// For the rest keys of the big map, move them to the small map and destroy them in the big map
	std::uninitialized_move(big.keys_ptr() + small.size(), big.keys_ptr() + big.size(), small.keys_ptr() + small.size());
	std::destroy(big.keys_ptr() + small.size(), big.keys_ptr() + big.size());

	// Swap the first n keys where n is the size of the smallest of the maps
	std::swap_ranges(small.values_ptr(), small.values_ptr() + small.size(), big.values_ptr());
	// For the rest keys of the big map, move them to the small map and destroy them in the big map
	std::uninitialized_move(big.values_ptr() + small.size(), big.values_ptr() + big.size(), small.values_ptr() + small.size());
	std::destroy(big.values_ptr() + small.size(), big.values_ptr() + big.size());

	// Swap compare function and size
	std::swap(get_stored_compare(), other.get_stored_compare());
	std::swap(mSize, other.mSize);
}

template <typename Key, typename T, typename Compare, typename Allocator1, typename Allocator2>
bool operator == (const array_map<Key, T, Compare, Allocator1> & a, const array_map<Key, T, Compare, Allocator2> & b)
{
	return
		a.size() == b.size() &&
		std::equal(a.keys().begin(), a.keys().end(), b.keys().begin(), b.keys().end()) &&
		std::equal(a.values().begin(), a.values().end(), b.values().begin(), b.values().end());
}

template <typename Key, typename T, typename Compare, typename Allocator1, typename Allocator2>
bool operator != (const array_map<Key, T, Compare, Allocator1> & a, const array_map<Key, T, Compare, Allocator2> & b)
{
	return !(a == b);
}

template <typename Key, typename T, typename Compare, typename Allocator1, typename Allocator2>
bool operator < (const array_map<Key, T, Compare, Allocator1> & a, const array_map<Key, T, Compare, Allocator2> & b)
{
	return std::lexicographical_compare(a.keys().begin(), a.keys().end(), b.keys().begin(), b.keys().end());
}

template <typename Key, typename T, typename Compare, typename Allocator1, typename Allocator2>
bool operator <= (const array_map<Key, T, Compare, Allocator1> & a, const array_map<Key, T, Compare, Allocator2> & b)
{
	return !(a > b);
}

template <typename Key, typename T, typename Compare, typename Allocator1, typename Allocator2>
bool operator > (const array_map<Key, T, Compare, Allocator1> & a, const array_map<Key, T, Compare, Allocator2> & b)
{
	return b < a;
}

template <typename Key, typename T, typename Compare, typename Allocator1, typename Allocator2>
bool operator >= (const array_map<Key, T, Compare, Allocator1> & a, const array_map<Key, T, Compare, Allocator2> & b)
{
	return !(a < b);
}

namespace std
{
	template <typename Key, typename T, typename Compare, typename Allocator>
	void swap(array_map<Key, T, Compare, Allocator> & a, array_map<Key, T, Compare, Allocator> & b)
	{
		a.swap(b);
	}
}
