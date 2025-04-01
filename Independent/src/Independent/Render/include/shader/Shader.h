#pragma once

#include "Independent/Core/include/containers/String.h"

#include <glm/glm.hpp>

namespace Independent {

	class Shader
	{
	public:
		Shader(const String& vertexSrc, const String& fragmentSrc);
		~Shader();

		void Bind() const;
		void UnBind() const;

		void UploadUniformMat4(const String& name, const glm::mat4& matrix);
	private:
		uint32_t m_RendererID;
	};
}