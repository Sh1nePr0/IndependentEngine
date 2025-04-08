#pragma once
#include "Independent/Core/include/containers/SharedPtr.h"
#include "Independent/Core/include/containers/String.h"

namespace Independent {

	class Texture 
	{
	public:
		virtual ~Texture() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		static SharedPtr<Texture2D> Create(const String& path);
	};

}