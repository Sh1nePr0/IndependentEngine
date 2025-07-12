#include "idpdpch.h"
#include "Independent/Core/include/memory/StackMemoryResource.h"

namespace Independent {


	void* StackMemoryResource::allocate(size_t size, size_t alignment /*= alignof(std::max_align_t)*/)
	{
		std::uintptr_t current = reinterpret_cast<std::uintptr_t>(m_Base) + m_Offset;
		std::uintptr_t aligned = (current + alignment - 1) & ~(alignment - 1);
		std::size_t padding = aligned - current;

		if (m_Offset + padding + size > m_Capacity) return nullptr; // Out of memory

		m_Offset += padding + size;
		return reinterpret_cast<void*>(aligned);
	}

	size_t StackMemoryResource::getMarker() const 
	{
		return m_Offset;
	}

	void StackMemoryResource::reset()
	{
		m_Offset = 0;
	}

	void StackMemoryResource::freeTo(size_t marker)
	{
		m_Offset = marker;
	}

}