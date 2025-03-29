#pragma once


#include "Independent/Core/include/memory/BaseMemoryResource.h"

#include <queue>


namespace Independent {

	//TODO: Allocator implementation and integrate here
	template <typename T, typename Container = std::deque<T, BaseMemoryResourceAllocator<T>>>
	using Queue = std::queue<T>;

}