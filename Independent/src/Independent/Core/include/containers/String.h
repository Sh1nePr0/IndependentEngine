#pragma once

#include "Independent/Core/include/memory/BaseMemoryResource.h"

#include <string>

namespace Independent {

	//TODO: Allocator implementation and integrate here
	template <typename CharT, typename Traits = std::char_traits<CharT>, typename Allocator = BaseMemoryResourceAllocator<CharT>>
	using BasicString = std::basic_string<CharT, Traits>;

	using String = BasicString<char>;

	template <typename CharT>
	using BasicStringView = std::basic_string_view<CharT>;

	using StringView = BasicStringView<char>;
}