#pragma once

#include <memory>
#include <glm/glm.hpp>

#include "Independent/Render/include/vertex_array/VertexArray.h"

namespace Independent {

	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0,
			OpenGL = 1,
			Direct3D = 2,
			Vulkan = 3,
			Metal = 4
		};
	public:
		virtual void Clear() = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

		inline  static API GetAPI() { return s_API; }
	private:
		static API s_API;
	};

}
