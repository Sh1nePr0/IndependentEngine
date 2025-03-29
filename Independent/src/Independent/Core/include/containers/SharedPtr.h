#pragma once

#include "Independent/Core/include/memory/BaseMemoryResource.h"

#include <memory>


namespace Independent {

	//TODO: Allocator implementation and integrate here,
	//      Implement custom make shared or allocate shared function
	template <typename T>
	using SharedPtr = std::shared_ptr<T>;

	template <typename T>
	using WeakPtr = std::weak_ptr<T>;

	// SharedPtr<T> allocate_shared ...

	using std::static_pointer_cast;
	using std::dynamic_pointer_cast;

}