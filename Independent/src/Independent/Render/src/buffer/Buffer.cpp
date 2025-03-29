#include "idpdpch.h"
#include "Independent/Render/include/buffer/Buffer.h"

#include "Independent/Render/include/Renderer.h"
#include "Platform/OpenGL/include/OpenGLBuffer.h"


namespace Independent {

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:     IDPD_CORE_ASSERT(false, "RendererAPI::None is currrently not supported"); return nullptr;
		case RendererAPI::API::OpenGL:   return new OpenGLVertexBuffer(vertices, size);
		}

		IDPD_CORE_ASSERT(false, "Unknown RendereAPI");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:     IDPD_CORE_ASSERT(false, "RendererAPI::None is currrently not supported"); return nullptr;
		case RendererAPI::API::OpenGL:   return new OpenGLIndexBuffer(indices, size);
		}

		IDPD_CORE_ASSERT(false, "Unknown RendereAPI");
		return nullptr;
	}

}