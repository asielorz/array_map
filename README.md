# Array map

Array map is an ordered associative container, similar to std::map and boost::flat_map, except that instead of storing pairs of keys and values it has two separate arrays, one with all the keys and one with all the values. The key at each index corresponds to the value at the same index. This is meant to optimize the most common operation on map: search. Search on sorted maps is done by binary searching the keys for the desired one, then returning the value associated to that key. If values are stored next to keys, we will bloat the cache with the memory for the values while binary searching, when the only thing we care about is the keys. By storing only the keys in an array, the signal to noise ratio in the cached memory is maximized, therefore speeding up the search. Then, a single access is done to the potentially cold array of values.

Insertion and removal are linear, and search is logarithmic. Construction from a range is n log(n).

## Compressed pair

Compressed pair is used to store the allocator and the compare function in 0 bytes if they are empty, getting advantage of empty base class optimization. It is practically the same as boost::compressed_pair.

## Algorithm

The algorithm file contains algorithms necessary for implementing the data structure, in a templated generalized manner so that they can be used for other code. It also contains some standard algorithms from C++17 because this was developed in C++14.

## Array view

array_view is a useful wrapper around a T pointer and a size, providing iterators and some helpful methods.