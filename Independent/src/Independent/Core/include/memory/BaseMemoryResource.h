#pragma once


namespace Independent {

	class BaseMemoryResource
	{
	public:
		virtual ~BaseMemoryResource() = default;

		virtual void* allocate(size_t size, size_t alignment) = 0;
		virtual void* reallocate(void* memory, size_t size, size_t alignment) = 0;
		virtual void  deallocate(void* memory) = 0;

		template <typename T>
		T* allocate(size_t count = 1)
		{
			return static_cast<T*>(allocate(sizeof(T) * count, alignof(T)));
		}

		template <typename T, typename... Args>
		T* construct(Args&&... args)
		{
			return new (allocate<T>()) T(std::forward<Args>(args)...);
		}
	};


	template <typename T>
	class BaseMemoryResourceAllocator
	{
	public:

		BaseMemoryResourceAllocator(BaseMemoryResource& cntr_memory_resource)
			: memory_resource = cntr_memory_resource
		{
		}

		template <typename U>
		BaseMemoryResourceAllocator(const BaseMemoryResourceAllocator<U>& allocator)
			: memory_resource(allocator.memory_resource)
		{
		}

		T* allocate(size_t count)
		{
			return memory_resource->allocate<T>(count);
		}

		void deallocate(T* memory, size_t count)
		{
			memory_resource->deallocate(memory);
		}

		bool operator==(const BaseMemoryResourceAllocator& other) const
		{
			return memory_resource == other.memory_resource;
		}

		bool operator!=(const BaseMemoryResourceAllocator& other) const
		{
			return memory_resource != other.memory_resource;
		}

		BaseMemoryResource* memory_resource;
	};
}