#pragma once


#include "Independent/Core/include/memory/BaseMemoryResource.h"

#include <set>

namespace Independent {

	//TODO: Allocator implementation and integrate here
	template <typename Key, typename Comparator = std::less<Key>, typename Allocator = BaseMemoryResourceAllocator<Key>>
	using Set = std::set<Key, Comparator>;

}