#include "idpdpch.h"

#include "Independent/Render/include/Renderer2D.h"
#include "Independent/Render/include/vertex_array/VertexArray.h"
#include "Independent/Render/include/shader/Shader.h"

#include "Platform/OpenGL/include/OpenGLShader.h"

namespace Independent {

	struct Renderer2DData
	{
		SharedPtr<VertexArray> QuadVertexArray;
		SharedPtr<Shader> FlatColorShader;
	};

	static Renderer2DData* s_Renderer2DData;

	void Renderer2D::Init()
	{
		s_Renderer2DData = new Renderer2DData();

		s_Renderer2DData->QuadVertexArray = VertexArray::Create();

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		SharedPtr<VertexBuffer> squareVBO;
		squareVBO = VertexBuffer::Create(squareVertices, sizeof(squareVertices));

		{
			BufferLayout squareVBOLayout = {
				{ ShaderDataType::Float3, "a_Position" }
			};

			squareVBO->SetLayout(squareVBOLayout);
		}

		s_Renderer2DData->QuadVertexArray->AddVertexBuffer(squareVBO);

		uint32_t squareIndices[6] = {
			0, 1 , 2 , 2, 3 ,0
		};

		SharedPtr<IndexBuffer> squareIBO;
		squareIBO = IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		s_Renderer2DData->QuadVertexArray->SetIndexBuffer(squareIBO);

		s_Renderer2DData->FlatColorShader = Shader::Create("assets/shaders/FlatColor.glsl");
	}

	void Renderer2D::Shutdown()
	{
		delete s_Renderer2DData;
	}

	void Renderer2D::BeginScene(const SharedPtr<CameraBase>& camera)
	{
		std::dynamic_pointer_cast<OpenGLShader>(s_Renderer2DData->FlatColorShader)->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(s_Renderer2DData->FlatColorShader)->UploadUniformMat4("u_ViewProjection", camera->GetViewProjectionMatrix());
		std::dynamic_pointer_cast<OpenGLShader>(s_Renderer2DData->FlatColorShader)->UploadUniformMat4("u_Transform", glm::mat4(1.0f));
	}

	void Renderer2D::EndScene()
	{

	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		std::dynamic_pointer_cast<OpenGLShader>(s_Renderer2DData->FlatColorShader)->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(s_Renderer2DData->FlatColorShader)->UploadUniformFloat4("u_Color", color);

		s_Renderer2DData->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Renderer2DData->QuadVertexArray);
	}

}