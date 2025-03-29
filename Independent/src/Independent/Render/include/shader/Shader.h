#pragma once

#include "Independent/Core/include/containers/String.h"

namespace Independent {

	class Shader
	{
	public:
		Shader(const String& vertexSrc, const String& fragmentSrc);
		~Shader();

		void Bind() const;
		void UnBind() const;
	private:
		uint32_t m_RendererID;
	};
}