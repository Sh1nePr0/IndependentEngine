#pragma once

#include "Independent/Core/include/memory/BaseMemoryResource.h"

#include <unordered_set>

namespace Independent {

	//TODO: Allocator implementation and integrate here
	template <typename Key, typename Hash = std::hash<Key>, typename KeyEqual = std::equal_to<Key>, typename Allocator = BaseMemoryResourceAllocator<Key>>
	using UnorderedSet = std::unordered_set<Key, Hash, KeyEqual>;

}