#pragma once


#include "Independent/Core/include/memory/BaseMemoryResource.h"

#include <unordered_map>

namespace Independent {

	//TODO: Allocator implementation and integrate here
	template <typename Key, typename T, typename Hash = std::hash<Key>, typename KeyEqual = std::equal_to<Key>, typename typename Allocator = BaseMemoryResourceAllocator<std::pair<const Key, T>>>
	using UnorderedMap = std::unordered_map<Key, T, Hash, KeyEqual>;

}