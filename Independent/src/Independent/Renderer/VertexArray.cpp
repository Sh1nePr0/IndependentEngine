#include "idpdpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Independent {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:     IDPD_CORE_ASSERT(false, "RendererAPI::None is currrently not supported"); return nullptr;
		case RendererAPI::OpenGL:   return new OpenGLVertexArray();
		}

		IDPD_CORE_ASSERT(false, "Unknown RendereAPI");
		return nullptr;
	}

}