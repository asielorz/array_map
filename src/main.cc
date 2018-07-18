#include "array_map.hh"
#include <vector>
#include <cassert>
#include <iostream>

std::vector<void(*)()> tests;

#if _DEBUG
#define debug_assert(expression) assert(expression)
#else
#define debug_assert(expression) static_cast<void>(expression)
#endif

#define assert_unreachable debug_assert(false && "Control should never reach this point")

struct call_on_init
{
	template <typename Callable>
	call_on_init(Callable c)
	{
		c();
	}
};

#define TEST(test_name)																	\
void test_name();																		\
::call_on_init __##test_name##__register_test{ [](){ tests.emplace_back(&test_name); }};\
																						\
void test_name()																		\
																						\

#define IGNORE_TEST(test_name) void test_name()

int main()
{
	for (const auto & test : tests)
		test();
}

TEST(can_construct_empty_table_of_pair_of_types)
{
	array_map<int, int> table;
	debug_assert(table.empty());
	debug_assert(table.size() == 0);
}

TEST(can_insert_pairs_of_key_value)
{
	array_map<int, int> table;
	table.insert(3, 4);
	table.insert(6, 1);
	table.insert(2, 4);
	debug_assert(table.size() == 3);
}

TEST(inserting_ignores_duplicate_keys)
{
	array_map<int, int> table;
	table.insert(1, 1);
	table.insert(1, 2);
	table.insert(1, 3);
	table.insert(1, 4);
	table.insert(1, 5);
	table.insert(1, 5);
	table.insert(1, 6);

	debug_assert(table.size() == 1);
}

TEST(capacity_grows_exponentially)
{
	array_map<int, int> table;
	debug_assert(table.capacity() == 0);

	table.insert(1, 1);
	debug_assert(table.capacity() == 1);

	table.insert(2, 1);
	debug_assert(table.capacity() == 2);

	table.insert(3, 1);
	debug_assert(table.capacity() == 4);

	table.insert(4, 1);
	debug_assert(table.capacity() == 4);

	table.insert(5, 1);
	debug_assert(table.capacity() == 8);
}

TEST(at_returns_reference_to_value_associated_to_a_key)
{
	array_map<int, int> table;
	table.insert(3, 4);
	table.insert(6, 1);
	table.insert(2, 7);

	debug_assert(table.at(3) == 4);
	debug_assert(table.at(6) == 1);
	debug_assert(table.at(2) == 7);

	table.at(3) = 5;
	debug_assert(table.at(3) == 5);
}

TEST(at_throws_if_doesnt_find)
{
	array_map<int, int> table;
	
	try
	{
		table.at(4) = 5;
		assert_unreachable;
	}
	catch (const std::exception &)
	{}
}

TEST(subscript_returns_reference_to_value_associated_to_a_key)
{
	array_map<int, int> table;

	table.insert(2, 4);
	debug_assert(table[2] == 4);

	table[2] = 5;
	debug_assert(table[2] == 5);
}

TEST(subscript_inserts_new_default_constructed_element_with_given_key_if_not_found)
{
	array_map<int, int> table;
	table[4] = 1;
	debug_assert(table[4] == 1);
	debug_assert(table.size() == 1);
}

TEST(clear_destroys_all_elements_but_lets_capacity_unchanged)
{
	array_map<int, int> table;
	table[4] = 1;
	table[6] = 2;
	table[8] = 1;
	table[2] = 0;

	debug_assert(table.size() == 4);
	debug_assert(table.capacity() == 4);

	table.clear();

	debug_assert(table.size() == 0);
	debug_assert(table.capacity() == 4);
}

TEST(shrink_to_fit_releases_memory_so_that_capacity_equals_size)
{
	array_map<int, int> table;
	table.reserve(25);
	table[4] = 1;
	table[6] = 2;
	table[8] = 1;
	table[2] = 0;

	debug_assert(table.size() == 4);
	debug_assert(table.capacity() == 25);

	table.shrink_to_fit();

	debug_assert(table.size() == 4);
	debug_assert(table.capacity() == 4);
	debug_assert(table[4] == 1);
	debug_assert(table[6] == 2);
	debug_assert(table[8] == 1);
	debug_assert(table[2] == 0);
}

TEST(begin_returns_iterator_to_first_element)
{
	array_map<int, int> table;
	table[4] = 1;
	table[6] = 2;
	table[8] = 1;
	table[2] = 0;

	debug_assert(table.begin()->key == 2);
	debug_assert(table.begin()->value == 0);
}

TEST(table_can_be_iterated_with_range_for)
{
	array_map<int, int> table;
	table[1] = 1;
	table[0] = 0;
	table[3] = 3;
	table[2] = 2;

	int i = 0;
	for (const auto & elem : table)
	{
		debug_assert(elem.key == i);
		debug_assert(elem.value == i);
		++i;
	}

	debug_assert(i == 4);
}

TEST(const_table_can_be_iterated)
{
	array_map<int, int> table;
	table[1] = 1;
	table[0] = 0;
	table[3] = 3;
	table[2] = 2;
	const array_map<int, int> & const_table = table;

	int i = 0;
	for (const auto & elem : const_table)
	{
		debug_assert(elem.key == i);
		debug_assert(elem.value == i);
		++i;
	}

	debug_assert(i == 4);
}

TEST(table_can_be_reverse_iterated)
{
	array_map<int, int> table;
	table[1] = 1;
	table[0] = 0;
	table[3] = 3;
	table[2] = 2;

	int i = 3;
	for (auto it = table.rbegin(); it < table.rend(); ++it)
	{
		debug_assert(it->key == i);
		debug_assert(it->value == i);
		--i;
	}

	debug_assert(i == -1);
}

TEST(insert_returns_whether_element_was_inserted_and_iterator_to_position)
{
	array_map<int, int> table;
	const auto r = table.insert(1, 4);
	debug_assert(r.second == true);
	debug_assert(r.first->value == 4);

	const auto r2 = table.insert(1, 6);
	debug_assert(r2.second == false);
	debug_assert(r2.first->value == 4);
}

TEST(insert_can_take_a_hint_to_insert_in_constant_time)
{
	array_map<int, int> table;
	table.insert(table.begin(), 4, 2);
	table.insert(table.begin(), 2, 4);
	table.insert(table.end(), 7, 1);
}

TEST(find_returns_iterator_to_the_element_with_the_given_key)
{
	array_map<int, int> table;
	table.insert(table.begin(), 4, 2);
	table.insert(table.begin(), 2, 4);
	table.insert(table.end(), 7, 1);

	array_map<int, int>::iterator it = table.find(4);
	debug_assert(it->key == 4);
	debug_assert(it->value == 2);

	const auto & const_table = table;
	array_map<int, int>::const_iterator cit = const_table.find(7);
	debug_assert(cit->key == 7);
	debug_assert(cit->value == 1);
}

TEST(find_returns_end_on_failure)
{
	array_map<int, int> table;
	debug_assert(table.find(5) == table.end());
}

TEST(lower_bound_returns_iterator_to_element_of_given_key_or_next_element_if_not_found)
{
	array_map<int, int> table;
	table.insert(table.begin(), 4, 2);
	table.insert(table.begin(), 2, 4);
	table.insert(table.end(), 7, 1);

	debug_assert(table.lower_bound(4)->key == 4);
	debug_assert(table.lower_bound(1)->key == 2);
	debug_assert(table.lower_bound(10) == table.end());
}

TEST(upper_bound_returns_iterator_to_element_next_to_the_given_key)
{
	array_map<int, int> table;
	table.insert(table.begin(), 4, 2);
	table.insert(table.begin(), 2, 4);
	table.insert(table.end(), 7, 1);

	debug_assert(table.upper_bound(4)->key == 7);
	debug_assert(table.upper_bound(1)->key == 2);
	debug_assert(table.upper_bound(10) == table.end());
}

TEST(array_map_is_copy_constructible)
{
	array_map<int, int> table;
	table.insert(table.begin(), 4, 2);
	table.insert(table.begin(), 2, 4);
	table.insert(table.end(), 7, 1);

	auto table2 = table;

	debug_assert(table2.size() == 3);
	debug_assert(table2[4] == 2);
	debug_assert(table2[2] == 4);
	debug_assert(table2[7] == 1);
}

TEST(array_map_is_copy_assignable)
{
	array_map<int, int> table, table2;
	table.insert(table.begin(), 4, 2);
	table.insert(table.begin(), 2, 4);
	table.insert(table.end(), 7, 1);

	table2 = table;

	debug_assert(table2.size() == 3);
	debug_assert(table2[4] == 2);
	debug_assert(table2[2] == 4);
	debug_assert(table2[7] == 1);
}

TEST(array_map_is_move_constructible)
{
	array_map<int, int> table;
	table.insert(table.begin(), 4, 2);
	table.insert(table.begin(), 2, 4);
	table.insert(table.end(), 7, 1);

	auto table2 = std::move(table);

	debug_assert(table2.size() == 3);
	debug_assert(table2[4] == 2);
	debug_assert(table2[2] == 4);
	debug_assert(table2[7] == 1);
	debug_assert(table.size() == 0);
	debug_assert(table.capacity() == 0);
}

TEST(array_map_is_move_assignable)
{
	array_map<int, int> table, table2;
	table.insert(table.begin(), 4, 2);
	table.insert(table.begin(), 2, 4);
	table.insert(table.end(), 7, 1);

	table2 = std::move(table);

	debug_assert(table2.size() == 3);
	debug_assert(table2[4] == 2);
	debug_assert(table2[2] == 4);
	debug_assert(table2[7] == 1);
	debug_assert(table.size() == 0);
	debug_assert(table.capacity() == 0);
}

TEST(shrink_to_fit_with_size_zero_frees_all_memory_and_doesnt_allocate)
{
	array_map<int, int> table;
	table.insert(table.begin(), 4, 2);
	table.insert(table.begin(), 2, 4);
	table.insert(table.end(), 7, 1);

	debug_assert(table.size() == 3);
	debug_assert(table.capacity() == 4);

	table.clear();
	table.shrink_to_fit();

	debug_assert(table.size() == 0);
	debug_assert(table.capacity() == 0);
}

TEST(if_comp_is_transparent_can_use_any_type_as_key_for_at)
{
	array_map<std::string, int> table;
	table.insert("foo", 1);
	table.insert("bar", 2);
	table.insert("baz", 3);

	debug_assert(table.at("foo") == 1);
	debug_assert(table.at("bar") == 2);

	const auto & const_table = table;
	debug_assert(const_table.at("baz") == 3);
}

TEST(find_supports_transparent_comparison)
{
	array_map<std::string, int> table;
	const auto & const_table = table;
	table.insert("foo", 1);
	table.insert("bar", 2);
	table.insert("baz", 3);

	debug_assert(table.find("foo")->value == 1);
	debug_assert(table.find("bar")->value == 2);
	debug_assert(const_table.find("baz")->value == 3);
}

TEST(lower_bound_supports_transparent_comparison)
{
	array_map<std::string, int> table;
	const auto & const_table = table;
	table.insert("foo", 1);
	table.insert("bar", 2);
	table.insert("baz", 3);

	debug_assert(table.lower_bound("foo")->value == 1);
	debug_assert(table.lower_bound("ban")->value == 2);
	debug_assert(const_table.lower_bound("bax")->value == 3);
	debug_assert(const_table.lower_bound("zzzyx") == const_table.end());
}

TEST(upper_bound_supports_transparent_comparison)
{
	array_map<std::string, int> table;
	const auto & const_table = table;
	table.insert("foo", 1);
	table.insert("bar", 2);
	table.insert("baz", 3);

	debug_assert(table.upper_bound("foo") == table.end());
	debug_assert(table.upper_bound("ban")->value == 2);
	debug_assert(const_table.upper_bound("bax")->value == 3);
	debug_assert(const_table.upper_bound("zzzyx") == const_table.end());
}

TEST(emplace_constructs_a_value_from_the_given_arguments)
{
	array_map<int, std::string> table;
	table.emplace(4, 6, 'c');

	debug_assert(table[4] == "cccccc");
}

TEST(emplace_constructs_value_only_once_at_final_position)
{
	struct test_t
	{
		test_t(std::vector<test_t *> & constructed_instances)
		{
			constructed_instances.push_back(this);
		}
	};

	std::vector<test_t *> constructed_instances;

	array_map<int, test_t> table;
	table.emplace(4, constructed_instances);

	debug_assert(constructed_instances.size() == 1);
	debug_assert(constructed_instances[0] == &table.at(4));
}

TEST(emplace_can_take_a_hint_and_tries_to_emplace_right_before_hint_if_possible)
{
	array_map<int, std::string> table;
	table.insert(2, "foo");
	table.insert(6, "bar");
	table.emplace(table.find(6), 4, 6, 'c');

	debug_assert(table[4] == "cccccc");
}

TEST(array_map_is_equality_comparable)
{
	array_map<int, std::string> table;
	table.insert(2, "foo");
	table.insert(6, "bar");
	table.emplace(table.find(6), 4, 6, 'c');

	array_map<int, std::string> table2 = table;
	array_map<int, std::string> table3 = table;
	table3[6] = "Howdy!";

	debug_assert(table == table2);
	debug_assert(table != table3);
}

TEST(erase_removes_element_pointed_to_by_given_iterator)
{
	array_map<int, std::string> table;
	table.insert(2, "foo");
	table.insert(6, "bar");
	table.emplace(table.find(6), 4, 6, 'c');

	table.erase(table.begin());
	debug_assert(table.size() == 2);
	debug_assert(table[6] == "bar");
	debug_assert(table[4] == "cccccc");

	table.erase(table.find(6));
	debug_assert(table.size() == 1);
	debug_assert(table[4] == "cccccc");
}

TEST(erase_with_iterator_pair_removes_the_whole_range)
{
	array_map<int, int> table;
	table.insert(1, 1);
	table.insert(2, 2);
	table.insert(3, 3);
	table.insert(4, 4);
	table.insert(5, 5);
	table.insert(6, 6);
	table.insert(7, 7);
	table.insert(8, 8);

	table.erase(table.find(4), table.find(8));
	debug_assert(table.size() == 4);
	try
	{
		debug_assert(table.at(1) == 1);
		debug_assert(table.at(2) == 2);
		debug_assert(table.at(3) == 3);
		debug_assert(table.at(8) == 8);
	}
	catch (const std::exception &)
	{
		assert_unreachable;
	}
}

TEST(erase_with_key_removes_element_with_that_key_if_found)
{
	array_map<int, int> table;
	table.insert(1, 1);
	table.insert(2, 2);
	table.insert(3, 3);
	table.insert(4, 4);
	table.insert(5, 5);
	table.insert(6, 6);
	table.insert(7, 7);
	table.insert(8, 8);

	const auto erased = table.erase(4);
	debug_assert(erased == 1);

	try
	{
		table.at(4) = 5; // Should throw
		assert_unreachable;
	}
	catch(const std::exception &)
	{}

	const auto erased2 = table.erase(4);
	debug_assert(erased2 == 0);
}

TEST(is_comparable_evaluates_to_true_if_two_types_can_be_compared_with_a_given_compare_function)
{
	static_assert(is_comparable<std::string, std::string, std::less<>>::value == true, "");
	static_assert(is_comparable<std::string, const char *, std::less<>>::value == true, "");
	static_assert(is_comparable<std::string, int, std::less<>>::value == false, "");
}

TEST(erase_supports_transparent_comparison)
{
	array_map<std::string, int> table;
	table.insert("foo", 1);
	table.insert("bar", 2);
	table.emplace("baz", 3);

	table.erase("baz");
}

TEST(if_compare_and_allocator_are_empty_size_of_array_map_is_size_of_three_pointers)
{
	static_assert(sizeof(array_map<int, int>) == 3 * sizeof(void *), "");
}

TEST(can_iterate_over_keys_of_a_map)
{
	array_map<std::string, int> table;
	table.insert("foo", 1);
	table.insert("bar", 2);
	table.emplace("baz", 3);

	size_t counter = 0;
	std::string keys[] = { "bar", "baz", "foo" };
	for (const auto & key : table.keys())
		debug_assert(key == keys[counter++]);
}

TEST(can_iterate_over_values_of_a_map)
{
	array_map<std::string, int> table;
	table.insert("foo", 1);
	table.insert("bar", 2);
	table.emplace("baz", 3);

	for (auto & v : table.values())
		v = 4;

	debug_assert(table["foo"] == 4);
	debug_assert(table["bar"] == 4);
	debug_assert(table["baz"] == 4);
}

TEST(can_construct_a_map_from_an_initializer_list)
{
	const array_map<std::string, int> map = {
		{ "foo",  5 },
		{ "bar",  7 },
		{ "baz", -1 }
	};

	debug_assert(map.size() == 3);
	debug_assert(map.capacity() == 3);
	try
	{
		debug_assert(map.at("foo") == 5);
		debug_assert(map.at("bar") == 7);
		debug_assert(map.at("baz") == -1);
	}
	catch (const std::exception &)
	{
		assert_unreachable;
	}
}

TEST(can_specify_that_initializer_list_is_already_sorted_and_unique_for_faster_construction)
{
	const array_map<std::string, int> map(ordered_unique_range, {
		{ "bar",  7 },
		{ "baz", -1 },
		{ "foo",  5 }
	});

	debug_assert(map.size() == 3);
	debug_assert(map.capacity() == 3);
	try
	{
		debug_assert(map.at("foo") == 5);
		debug_assert(map.at("bar") == 7);
		debug_assert(map.at("baz") == -1);
	}
	catch (const std::exception &)
	{
		assert_unreachable;
	}
}

struct test_t
{
	static int count;

	test_t() noexcept { count++; }
	test_t(int i_) noexcept : i(i_) { count++; }
	test_t(const test_t & other) noexcept : i(other.i) { count++; }
	test_t(test_t && other) noexcept : i(other.i) { count++; }
	~test_t() { count--; }
	operator int() const noexcept { return i; }

	test_t & operator = (const test_t &) noexcept = default;
	test_t & operator = (test_t &&) noexcept = default;

	int i;
};

int test_t::count = 0;

TEST(each_object_is_constructed_and_destroyed_exactly_once)
{
	{
		array_map<std::string, test_t> map(ordered_unique_range, {
			{ "bar",  7 },
			{ "baz", -1 },
			{ "foo",  5 }
		});

		map.reserve(5);
		map.insert("quux", 6);
		map.insert("quux", 6);
		map.insert("quux", 6);

		map.erase("baz");

		map.shrink_to_fit();

		debug_assert(test_t::count == map.size());
	}
	debug_assert(test_t::count == 0);
}

TEST(specialization_of_std_swap_for_array_map_swaps_contents_of_containers)
{
	array_map<std::string, int> map1(ordered_unique_range, {
		{ "bar",  7 },
		{ "baz", -1 },
		{ "foo",  5 }
	});
	array_map<std::string, int> map2;
	
	std::swap(map1, map2);

	debug_assert(map1.empty());
	try
	{
		debug_assert(map2.at("bar") == 7);
		debug_assert(map2.at("baz") == -1);
		debug_assert(map2.at("foo") == 5);
	}
	catch (const std::exception &)
	{
		assert_unreachable;
	}
}

TEST(if_given_an_allocator_of_a_type_different_of_char_allocator_gets_rebound_to_char)
{
	using map_t = array_map<std::string, int, std::less<>, std::allocator<int>>;

	static_assert(std::is_same<map_t::allocator_type, std::allocator<int>>::value, "");
	static_assert(std::is_same<map_t::stored_allocator_type, std::allocator<char>>::value, "");
}
