#pragma once

#include "Independent/Core/include/memory/BaseMemoryResource.h"

#include <map>

namespace Independent {

	//TODO: Allocator implementation and integrate here
	template <typename Key, typename T, typename Comparator = std::less<Key>, typename Allocator = BaseMemoryResourceAllocator<std::pair<const Key, T>>>
	using Map = std::map < Key, T, Comparator>;

}
