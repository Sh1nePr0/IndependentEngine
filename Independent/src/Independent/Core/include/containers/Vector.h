#pragma once

#include "Independent/Core/include/memory/BaseMemoryResource.h"

#include <vector>


namespace Independent {

	//TODO: Allocator implementation and integrate here
	template <typename T, typename Allocator =  BaseMemoryResourceAllocator<T>>
	using Vector = std::vector<T>;

}