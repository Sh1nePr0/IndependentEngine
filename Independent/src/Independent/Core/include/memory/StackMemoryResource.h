#pragma once
#include <cstddef>

namespace Independent {

	class StackMemoryResource
	{
	public:
		explicit StackMemoryResource(std::size_t size)
			: m_Capacity(size)
		{
			m_Base = std::malloc(size);
		}

		~StackMemoryResource()
		{
			std::free(m_Base);
			m_Base = nullptr;
			m_Capacity = 0;
			m_Offset = 0;
		}

		void* allocate(size_t size, size_t alignment = alignof(std::max_align_t));

		template <typename T, typename... Args>
		T* construct(Args&&... args)
		{
			void* ptr = allocate(sizeof(T), alignof(T));
			return ptr ? new (ptr) T(std::forward<Args>(args)) : nullptr;
		}

		template <typename T>
		void destroy(T* obj)
		{
			if (obj)
			{
				obj->~T();
			}
		}

		size_t getMarker() const;

		void reset();

		void freeTo(size_t marker);

	private:
		void* m_Base;
		size_t m_Capacity;
		size_t m_Offset;
	};

}