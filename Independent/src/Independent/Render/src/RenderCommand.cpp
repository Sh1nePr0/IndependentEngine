#include "idpdpch.h"
#include "Independent/Render/include/RenderCommand.h"

#include "Platform/OpenGL/include/OpenGLRendererAPI.h"

namespace Independent {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}