#pragma once

#include "RenderCommand.h"
#include "Independent/Core/include/containers/SharedPtr.h"

namespace Independent {

	class Renderer
	{
	public:
		static void BeginScene();
		static void EndScene();

		static void Submit(const SharedPtr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
}