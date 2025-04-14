#pragma once

#include "RenderCommand.h"
#include "Independent/Render/include/camera/CameraBase.h"
#include "Independent/Render/include/texture/Texture.h"
#include <glm/glm.hpp>

namespace Independent {

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const SharedPtr<CameraBase>& camera);
		static void EndScene();

		// Primitives
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const SharedPtr<Texture2D>& texture);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const SharedPtr<Texture2D>& texture);
	};

}