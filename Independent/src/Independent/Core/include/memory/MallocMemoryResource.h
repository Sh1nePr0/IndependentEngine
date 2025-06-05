#pragma once

#include "Independent/Core/include/memory/BaseMemoryResource.h"

namespace Independent {

	class MallocMemoryResource : public BaseMemoryResource
	{
	public:
		static MallocMemoryResource& instance();

		MallocMemoryResource(const MallocMemoryResource& original) = delete;
		MallocMemoryResource(MallocMemoryResource&& original) = delete;

		~MallocMemoryResource() override = default;

		MallocMemoryResource& operator=(const MallocMemoryResource& original) = delete;
		MallocMemoryResource& operator=(MallocMemoryResource&& original) = delete;

		void* allocate(size_t size, size_t alignment) override;
		void* reallocate(void* memory, size_t size, size_t alignment) override;
		void deallocate(void* memory) override;

		using BaseMemoryResource::allocate;
	private:
		MallocMemoryResource() = default;
	};


}