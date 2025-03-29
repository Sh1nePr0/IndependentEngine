#include "idpdpch.h"
#include "Independent/Render/include/vertex_array/VertexArray.h"

#include "Independent/Render/include/Renderer.h"
#include "Platform/OpenGL/include/OpenGLVertexArray.h"

namespace Independent {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:     IDPD_CORE_ASSERT(false, "RendererAPI::None is currrently not supported"); return nullptr;
		case RendererAPI::API::OpenGL:   return new OpenGLVertexArray();
		}

		IDPD_CORE_ASSERT(false, "Unknown RendereAPI");
		return nullptr;
	}

}