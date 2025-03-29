#pragma once

#include "RendererAPI.h"
#include "Independent/Core/include/containers/SharedPtr.h"

namespace Independent {

	class RenderCommand
	{
	public:
		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}

		inline static void SetClearColor(const glm::vec4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}

		inline static void DrawIndexed(const SharedPtr<VertexArray>& vertexArray)
		{
			s_RendererAPI->DrawIndexed(vertexArray);
		}
	private:
		static RendererAPI* s_RendererAPI;
	};

}