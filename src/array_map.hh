#pragma once

#include "compressed_pair.hh"
#include "array_view.hh"
#include "algorithm.hh"
#include <functional>
#include <memory>
#include <algorithm>
#include <iterator>
#include <cassert>

namespace detail
{
	template <typename T1, typename T2, typename Comp, typename = decltype(std::declval<Comp>()(std::declval<T1>(), std::declval<T2>()))>
	std::true_type is_comparable_impl(int *){}

	template <typename T1, typename T2, typename Comp>
	std::false_type is_comparable_impl(void *){}
}

//! Evaluates to true if the comparison function Comp can be invoked with T1 and T2 as arguments
template <typename T1, typename T2, typename Comp>
struct is_comparable : public decltype(detail::is_comparable_impl<T1, T2, Comp>(std::declval<int *>()))
{};

struct ordered_unique_range_t {} constexpr ordered_unique_range;

template <typename Key, typename T,	class Compare, class Allocator>
struct array_map;

namespace iterators
{
	template <typename Key, typename T>
	struct iterator_deref_t
	{
		const Key & key;
		T & value;
	};

	template <typename Key, typename T>
	struct iterator_arrow_t
	{
		// These two lines are boilerplate for std::reverse_iterator
		using element_type = iterator_deref_t<Key, T>;
		static iterator_arrow_t pointer_to(iterator_deref_t<Key, T> i) { return iterator_arrow_t(i); }

		iterator_arrow_t(iterator_deref_t<Key, T> i) noexcept : elem(i){}

		const iterator_deref_t<Key, T> * operator -> () const noexcept { return &elem; }

		iterator_deref_t<Key, T> elem;
	};

	template <typename Key, typename T, class Compare, class Allocator>
	struct array_map_const_iterator;

	template <
		typename Key,
		typename T,
		typename Compare,
		typename Allocator
	>
	struct array_map_iterator
	{
		using value_type = iterator_deref_t<Key, T>;
		using reference = value_type;
		using pointer = iterator_arrow_t<Key, T>;
		using difference_type = ptrdiff_t;
		using iterator_category = std::random_access_iterator_tag;

		array_map_iterator(array_map<Key, T, Compare, Allocator> * t, ptrdiff_t i) noexcept;

		array_map_iterator & operator ++ () noexcept;
		array_map_iterator   operator ++ (int) noexcept;
		array_map_iterator & operator -- () noexcept;
		array_map_iterator   operator -- (int) noexcept;

		array_map_iterator operator + (ptrdiff_t n) const noexcept;
		array_map_iterator operator - (ptrdiff_t n) const noexcept;

		array_map_iterator & operator += (ptrdiff_t n) noexcept;
		array_map_iterator & operator -= (ptrdiff_t n) noexcept;

		ptrdiff_t operator - (const array_map_iterator & other) const noexcept;

		bool operator == (const array_map_iterator & other) const noexcept;
		bool operator != (const array_map_iterator & other) const noexcept;
		bool operator < (const array_map_iterator & other) const noexcept;
		bool operator <= (const array_map_iterator & other) const noexcept;
		bool operator > (const array_map_iterator & other) const noexcept;
		bool operator >= (const array_map_iterator & other) const noexcept;

		value_type operator * () const noexcept;
		pointer operator -> () const noexcept;

		size_t index() const noexcept;
		array_map<Key, T, Compare, Allocator> * map() const noexcept;

		friend struct array_map_const_iterator<Key, T, Compare, Allocator>;

	private:
		array_map<Key, T, Compare, Allocator> * mMap;
		ptrdiff_t mIndex;
	};

	template <typename Key, typename T, class Compare, class Allocator>
	array_map_iterator<Key, T, Compare, Allocator> operator + (ptrdiff_t n, const array_map_iterator<Key, T, Compare, Allocator> & it) noexcept;


	template <
		typename Key,
		typename T,
		typename Compare,
		typename Allocator
	>
		struct array_map_const_iterator
	{
		using value_type = iterator_deref_t<Key, const T>;
		using reference = value_type;
		using pointer = iterator_arrow_t<Key, const T>;
		using difference_type = ptrdiff_t;
		using iterator_category = std::random_access_iterator_tag;

		array_map_const_iterator(const array_map<Key, T, Compare, Allocator> * t, ptrdiff_t i) noexcept;
		array_map_const_iterator(const array_map_iterator<Key, T, Compare, Allocator> & it) noexcept;

		array_map_const_iterator & operator ++ () noexcept;
		array_map_const_iterator   operator ++ (int) noexcept;
		array_map_const_iterator & operator -- () noexcept;
		array_map_const_iterator   operator -- (int) noexcept;

		array_map_const_iterator operator + (ptrdiff_t n) const noexcept;
		array_map_const_iterator operator - (ptrdiff_t n) const noexcept;

		array_map_const_iterator & operator += (ptrdiff_t n) noexcept;
		array_map_const_iterator & operator -= (ptrdiff_t n) noexcept;

		ptrdiff_t operator - (const array_map_const_iterator & other) const noexcept;

		bool operator == (const array_map_const_iterator & other) const noexcept;
		bool operator != (const array_map_const_iterator & other) const noexcept;
		bool operator < (const array_map_const_iterator & other) const noexcept;
		bool operator <= (const array_map_const_iterator & other) const noexcept;
		bool operator > (const array_map_const_iterator & other) const noexcept;
		bool operator >= (const array_map_const_iterator & other) const noexcept;

		value_type operator * () const noexcept;
		pointer operator -> () const noexcept;

		size_t index() const noexcept;
		const array_map<Key, T, Compare, Allocator> * map() const noexcept;

		friend struct array_map<Key, T, Compare, Allocator>;

	private:
		const array_map<Key, T, Compare, Allocator> * mMap;
		ptrdiff_t mIndex;
	};

	template <typename Key, typename T, class Compare, class Allocator>
	array_map_const_iterator<Key, T, Compare, Allocator> operator + (ptrdiff_t n, const array_map_const_iterator<Key, T, Compare, Allocator> & it) noexcept;

}

template <
	typename Key, 
	typename T, 
	typename Compare = std::less<>,
	typename Allocator = std::allocator<char>
>
struct array_map : private Compare
{
	using key_type = Key;
	using mapped_type = T;
	using key_compare = Compare;
	using allocator_type = Allocator;
	using stored_allocator_type = typename std::allocator_traits<allocator_type>::template rebind_alloc<char>;
	
	using iterator = iterators::array_map_iterator<Key, T, Compare, Allocator>;
	using const_iterator = iterators::array_map_const_iterator<Key, T, Compare, Allocator>;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

private:
	using allocator_traits = std::allocator_traits<stored_allocator_type>;
	static const bool move_assignment_is_noexcept = allocator_traits::propagate_on_container_move_assignment::value || 
		(std::is_nothrow_move_constructible<Key>::value && std::is_nothrow_move_constructible<T>::value);

public:
	//! Constructs an empty container
	array_map() = default;
	//! Constructs the container with custom compare function and allocator
	explicit array_map(const Compare & comp, const Allocator & alloc = Allocator());
	//! Constructs the container with custom allocator
	explicit array_map(const Allocator & alloc);

	//! Constructs the container from the contents of the initializer list
	array_map(std::initializer_list<std::pair<Key, T>> ilist, const Compare & comp = Compare(), const Allocator & alloc = Allocator());
	//! Constructs the container from the contents of the initializer list. Assumes the list is sorted and each key is unique, and the
	//! container will be ill-formed if not
	array_map(ordered_unique_range_t, std::initializer_list<std::pair<Key, T>> ilist, const Compare & comp = Compare(), const Allocator & alloc = Allocator());

	//! Copy constructor
	array_map(const array_map & other);
	array_map(const array_map & other, const Allocator & alloc);
	//! Copy assignment
	array_map & operator = (const array_map & other);
	//! Move constructor
	array_map(array_map && other) noexcept;
	array_map(array_map && other, const Allocator & alloc) noexcept;
	//! Move assignment
	array_map & operator = (array_map && other) noexcept(move_assignment_is_noexcept);

	//! Destructor frees all dynamic memory
	~array_map();

	//! Swaps the contents of two containers
	void swap(array_map & other);

	//! True if the container doesn't contain any element
	bool empty() const noexcept;
	//! Number of elements in the container
	size_t size() const noexcept;
	//! Number of elements that can be held in the currently allocated storage before having to reallocate
	size_t capacity() const noexcept;

	//! Returns an array_view to the keys stored in the container, sorted with respect to Compare
	array_view<const Key> keys() const noexcept;
	//! Returns an array_view to the values in the container, sorted with respect to their keys
	array_view<T> values() noexcept;
	array_view<const T> values() const noexcept;

	//! Inserts an element with given key and value
	std::pair<iterator, bool> insert(Key key, T value);
	//! Inserts an element with given key and value. If possible, inserts it just before hint and performs insertion in constant time
	iterator insert(const_iterator hint, Key key, T value);

	//! Inserts an element with the given key. Value is constructed in place with given arguments
	template <typename ... Args>
	std::pair<iterator, bool> emplace(Key key, Args && ... value_ctor_args);
	//! Inserts an element with the given key. Value is constructed in place with given arguments
	//! If possible, inserts it just before hint and performs insertion in constant time
	template <typename ... Args>
	iterator emplace(const_iterator hint, Key key, Args && ... value_ctor_args);

	//! Destroys all elements of the container. Capacity remains unchanged
	void clear() noexcept;
	//! Resizes so that capacity equals size
	void shrink_to_fit();
	//! Allocates memory to fit new_capacity elements in the container
	void reserve(size_t new_capacity);

	//! Returns the value associated to the given key, or throws std::out_of_range if not found
	T & at(const Key & key);
	const T & at(const Key & key) const;

	//! Transparent at
	template <typename TKey, typename Comp = Compare, typename = typename Comp::is_transparent, typename = std::enable_if_t<is_comparable<Key, TKey, Comp>::value>>
	T & at(const TKey & key);
	template <typename TKey, typename Comp = Compare, typename = typename Comp::is_transparent, typename = std::enable_if_t<is_comparable<Key, TKey, Comp>::value>>
	const T & at(const TKey & key) const;

	//! Returns the value associated to the given key, or inserts a new one and returns it if not found
	T & operator [] (const Key & key);
	T & operator [] (Key && key);

	//! Returns an iterator to the key-value pair with given key, or end if not found
	iterator find(const Key & key) noexcept;
	const_iterator find(const Key & key) const noexcept;

	//! Transparent find
	template <typename TKey, typename Comp = Compare, typename = typename Comp::is_transparent, typename = std::enable_if_t<is_comparable<Key, TKey, Comp>::value>>
	iterator find(const TKey & key) noexcept;
	template <typename TKey, typename Comp = Compare, typename = typename Comp::is_transparent, typename = std::enable_if_t<is_comparable<Key, TKey, Comp>::value>>
	const_iterator find(const TKey & key) const noexcept;

	//! Returns an iterator to the first element not less than the given key
	iterator lower_bound(const Key & key) noexcept;
	const_iterator lower_bound(const Key & key) const noexcept;

	// Transparent lower bound
	template <typename TKey, typename Comp = Compare, typename = typename Comp::is_transparent, typename = std::enable_if_t<is_comparable<Key, TKey, Comp>::value>>
	iterator lower_bound(const TKey & key) noexcept;
	template <typename TKey, typename Comp = Compare, typename = typename Comp::is_transparent, typename = std::enable_if_t<is_comparable<Key, TKey, Comp>::value>>
	const_iterator lower_bound(const TKey & key) const noexcept;

	//! Returns an iterator to the first element greater than the given key
	iterator upper_bound(const Key & key) noexcept;
	const_iterator upper_bound(const Key & key) const noexcept;

	//! Transparent upper bound
	template <typename TKey, typename Comp = Compare, typename = typename Comp::is_transparent, typename = std::enable_if_t<is_comparable<Key, TKey, Comp>::value>>
	iterator upper_bound(const TKey & key) noexcept;
	template <typename TKey, typename Comp = Compare, typename = typename Comp::is_transparent, typename = std::enable_if_t<is_comparable<Key, TKey, Comp>::value>>
	const_iterator upper_bound(const TKey & key) const noexcept;

	//! Removes element at pos. Returns iterator pointing at element following the erased element
	iterator erase(iterator pos);
	//! Removes elements at [first, last). Returns iterator pointing at element following the last erased element
	iterator erase(const_iterator first, const_iterator last);
	//! Removes element with given key if found. Returns the number of elements removed (1 if found, 0 if not)
	size_t erase(const Key & key);
	//! Transparent erase
	template <typename TKey, typename Comp = Compare, typename = typename Comp::is_transparent, typename = std::enable_if_t<is_comparable<Key, TKey, Comp>::value>>
	size_t erase(const TKey & key);

	//! Returns an iterator to the first element
	iterator begin() noexcept;
	const_iterator begin() const noexcept;
	const_iterator cbegin() const noexcept;
	//! Returns an iterator to one past the last element
	iterator end() noexcept;
	const_iterator end() const noexcept;
	const_iterator cend() const noexcept;

	//! Returns a reverse iterator to the last element
	reverse_iterator rbegin() noexcept;
	const_reverse_iterator rbegin() const noexcept;
	const_reverse_iterator crbegin() const noexcept;
	//! Returns a reverse iterator to one before the first element
	reverse_iterator rend() noexcept;
	const_reverse_iterator rend() const noexcept;
	const_reverse_iterator crend() const noexcept;

	//! Returns an iterator to the nth element
	iterator nth(size_t n) noexcept;
	const_iterator nth(size_t n) const noexcept;

	//! Returns the comparison function
	Compare key_comp() const noexcept;
	//! Returns the allocator
	Allocator get_allocator() const noexcept;
	//! Access allocator by reference
	stored_allocator_type & get_stored_allocator() noexcept;
	const stored_allocator_type & get_stored_allocator() const noexcept;
	
	friend struct iterators::array_map_iterator<Key, T, Compare, Allocator>;
	friend struct iterators::array_map_const_iterator<Key, T, Compare, Allocator>;

private:
	//! Accesses the array of keys. This function returns a pointer such that the range [keys, keys + size) is a valid
	//! range and contains all the keys of the container sorted with respect to comp
	const Key * keys_ptr() const noexcept;
	//! Mutable access to array of keys
	Key * keys_ptr() noexcept;
	//! Accesses the array of values. This function returns a pointer such that the range [values, values + size) is a valid
	//! range and contains all the values of the container sorted with respect to their key
	T * values_ptr() noexcept;
	const T * values_ptr() const noexcept;
	//! Given pointer to beginning of data array and capacity, returns pointer to array of values
	static T * value_array(void * data, size_t capacity) noexcept;
	static const T * value_array(const void * data, size_t capacity) noexcept;
	//! Accesses key or value at the given index
	const Key & key_at(size_t index) const noexcept;
	T & value_at(size_t index) noexcept;
	const T & value_at(size_t index) const noexcept;

	//! Mutable access to compare function object
	Compare & get_stored_compare() noexcept;

	//! Given target capacity, returns number of bytes that need to be allocated to hold that number of key-value pairs
	static size_t capacity_to_bytes(size_t capacity);

	//! Grows capacity to double the size
	void grow();
	//! Changes capacity to given value. Doesn't perform any check
	void change_capacity(size_t new_capacity);

	//! True if both keys are equal as to !comp(a, b) && !comp(b, a)
	template <typename TKey1, typename TKey2>
	bool keys_equal(const TKey1 & a, const TKey2 & b) const noexcept;

	struct find_result
	{
		size_t index;
		bool found;
	};
	//! Performs lower bound binary search
	template <typename TKey> size_t lower_bound_index(const TKey & key) const noexcept;
	//! Performs upper bound binary search
	template <typename TKey> size_t upper_bound_index(const TKey & key) const noexcept;
	//! Performs lower bound binary search. Returns index of search and whether the key was found or not
	template <typename TKey> find_result find_index_of(const TKey & key) const noexcept;

	struct insert_result
	{
		size_t index;
		bool inserted;
	};
	//! Inserts new element with given key at correct position. Value is constructed in place
	template <typename ... Args>
	insert_result insert_new_element(Key key, Args && ... args);
	//! Inserts new element with given key at correct position. If hint is exactly the next key to the given,
	//! inserts before hint in constant time. Value is constructed in place
	template <typename ... Args>
	insert_result insert_hint(const_iterator hint, Key key, Args && ... args);
	//! Inserts at the given index. Doesn't perform any check
	template <typename ... Args>
	insert_result insert_at_position(size_t index, Key key, Args && ... args); // No checks

	//! Destroys all elements
	void destroy_all() noexcept;
	//! Destroys all elements and frees dynamic memory
	void destroy_all_and_free() noexcept;

	//! Erases element at index i
	void erase_index(size_t i);

	//! Returns an array with capacity equal to other.size() allocated with alloc, and copies all keys
	//! and values from other to the new array
	static char * copy_other(const array_map & other, Allocator & alloc);
	//! Moves from other stealing other's internal array
	void move_from_other(array_map && other) noexcept;
	//! Allocates a new array and moves all keys and values from other one by one
	void move_from_other_without_propagation(array_map && other);

	//! Sets the value for capacity
	void set_capacity(size_t new_capacity) noexcept;

	//! Part of the copy assignment operator that depends on whether the allocator propagates or not, so that it
	//! can be dispatched at compile time through overloading
	void copy_assignment_allocator_propagation_dependant_code(const array_map & other, std::true_type);
	void copy_assignment_allocator_propagation_dependant_code(const array_map & other, std::false_type);

	//! Part of the move assignment operator that depends on whether the allocator propagates or not, so that it
	//! can be dispatched at compile time through overloading
	void move_assignment_allocator_propagation_dependant_code(array_map && other, std::true_type) noexcept(move_assignment_is_noexcept);
	void move_assignment_allocator_propagation_dependant_code(array_map && other, std::false_type) noexcept(move_assignment_is_noexcept);

	//! Part of the swap function that depends on whether the allocator propagates or not, so that it
	//! can be dispatched at compile time through overloading
	void swap_allocator_propagation_dependant_code(array_map & other, std::true_type);
	void swap_allocator_propagation_dependant_code(array_map & other, std::false_type);

	//! Swaps the contents of the containers assuming they can take ownership of the other's memory
	void swap_with_same_allocator(array_map & other);
	//! Swaps the contents of the containers assuming they can't take ownership of the other's memory
	void swap_with_different_allocator(array_map & other);

	compressed_pair<stored_allocator_type, size_t> mAllocatorAndCapacity = { stored_allocator_type(), 0 };	//!< Allocator and number of elements that the container can hold at most in currently allocated storage
	size_t mSize = 0;		//!< Number of elements in the container
	char * mData = nullptr;	//!< Pointer to the allocated buffer that stores the elements of the container
};

//! True if the contents of a and b are equal
template <typename Key, typename T, typename Compare, typename Allocator1, typename Allocator2>
bool operator == (const array_map<Key, T, Compare, Allocator1> & a, const array_map<Key, T, Compare, Allocator2> & b);

//! True if the contents of a and b are not equal
template <typename Key, typename T, typename Compare, typename Allocator1, typename Allocator2>
bool operator != (const array_map<Key, T, Compare, Allocator1> & a, const array_map<Key, T, Compare, Allocator2> & b);

//! Lexicographically compares the keys in a and b
template <typename Key, typename T, typename Compare, typename Allocator1, typename Allocator2>
bool operator < (const array_map<Key, T, Compare, Allocator1> & a, const array_map<Key, T, Compare, Allocator2> & b);

template <typename Key, typename T, typename Compare, typename Allocator1, typename Allocator2>
bool operator <= (const array_map<Key, T, Compare, Allocator1> & a, const array_map<Key, T, Compare, Allocator2> & b);

template <typename Key, typename T, typename Compare, typename Allocator1, typename Allocator2>
bool operator > (const array_map<Key, T, Compare, Allocator1> & a, const array_map<Key, T, Compare, Allocator2> & b);

template <typename Key, typename T, typename Compare, typename Allocator1, typename Allocator2>
bool operator >= (const array_map<Key, T, Compare, Allocator1> & a, const array_map<Key, T, Compare, Allocator2> & b);

namespace std
{
	//! Specialization of std::swap for array_map
	template <typename Key, typename T, typename Compare, typename Allocator>
	void swap(array_map<Key, T, Compare, Allocator> & a, array_map<Key, T, Compare, Allocator> & b);
}

#include "array_map.inl"
