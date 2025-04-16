#pragma once

#include "RenderCommand.h"
#include "Independent/Core/include/containers/SharedPtr.h"
#include "Independent/Render/include/camera/CameraBase.h"
#include "Independent/Render/include/shader/Shader.h"
#include <glm/glm.hpp>

namespace Independent {

	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();
		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginScene(const SharedPtr<CameraBase>& camera);
		static void EndScene();

		static void Submit(const SharedPtr<Shader>& shader, const SharedPtr<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));//, const glm::mat4& transform);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static UniquePtr<SceneData> s_SceneData;
	};
}