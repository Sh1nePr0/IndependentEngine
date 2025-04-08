#include "idpdpch.h"
#include "Independent/Render/include/texture/Texture.h"

#include "Independent/Render/include/Renderer.h"
#include "Platform/OpenGL/include/OpenGLTexture.h"

namespace Independent {

	SharedPtr<Texture2D> Texture2D::Create(const String& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:     IDPD_CORE_ASSERT(false, "RendererAPI::None is currrently not supported"); return nullptr;
		case RendererAPI::API::OpenGL:   return std::make_shared<OpenGLTexture2D>(path);
		}

		IDPD_CORE_ASSERT(false, "Unknown RendereAPI");
		return nullptr;
	}

}