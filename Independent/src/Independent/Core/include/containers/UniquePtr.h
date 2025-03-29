#pragma once

#include "Independent/Core/include/memory/BaseMemoryResource.h"

#include <memory>


namespace Independent {

	//TODO: Allocator implementation and integrate here,
	//      Implement custom deleter template classes,
	//      Implement make unique or allocate unique functions
	template <typename T, typename Allocator = BaseMemoryResourceAllocator<std::remove_extent_t<T>>>
	using UniquePtr = std::unique_ptr<T>;

}