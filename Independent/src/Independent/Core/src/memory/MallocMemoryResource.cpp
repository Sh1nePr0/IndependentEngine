#include "Independent/Core/include/memory/MallocMemoryResource.h"


#include "malloc.h"

namespace Independent {
	
	MallocMemoryResource& MallocMemoryResource::instance()
	{
		static MallocMemoryResource instance;
		return instance;
	}

	void* MallocMemoryResource::allocate(size_t size, size_t alignment)
	{
		// TODO: Add asserts for size and alignment
		return _aligned_malloc(size, alignment);
	}

	void* MallocMemoryResource::reallocate(void* memory, size_t size, size_t alignment)
	{
		// TODO: Add asserts for size and alignment
		return _aligned_realloc(memory, size, alignment);
	}

	void MallocMemoryResource::deallocate(void* memory)
	{
		_aligned_free(memory);
	}

}