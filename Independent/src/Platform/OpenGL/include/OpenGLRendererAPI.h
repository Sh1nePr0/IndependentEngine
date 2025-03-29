#pragma once

#include "Independent/Render/include/RendererAPI.h"
#include "Independent/Core/include/containers/SharedPtr.h"

namespace Independent {

	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Clear() override;
		virtual void SetClearColor(const glm::vec4& color) override;

		virtual void DrawIndexed(const SharedPtr<VertexArray>& vertexArray) override;
	};

}