#include "idpdpch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"


namespace Independent {

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:     IDPD_CORE_ASSERT(false, "RendererAPI::None is currrently not supported"); return nullptr;
		case RendererAPI::OpenGL:   return new OpenGLVertexBuffer(vertices, size);
		}

		IDPD_CORE_ASSERT(false, "Unknown RendereAPI");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:     IDPD_CORE_ASSERT(false, "RendererAPI::None is currrently not supported"); return nullptr;
		case RendererAPI::OpenGL:   return new OpenGLIndexBuffer(indices, size);
		}

		IDPD_CORE_ASSERT(false, "Unknown RendereAPI");
		return nullptr;
	}

}