#include "idpdpch.h"

#include "Independent/Render/include/Renderer2D.h"
#include "Independent/Render/include/vertex_array/VertexArray.h"
#include "Independent/Render/include/shader/Shader.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Independent {

	struct Renderer2DData
	{
		SharedPtr<VertexArray> QuadVertexArray;
		SharedPtr<Shader> TextureShader;
		SharedPtr<Texture2D> WhiteTexture;
	};

	static Renderer2DData* s_Renderer2DData;

	void Renderer2D::Init()
	{
		s_Renderer2DData = new Renderer2DData();

		s_Renderer2DData->QuadVertexArray = VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		SharedPtr<VertexBuffer> squareVBO;
		squareVBO = VertexBuffer::Create(squareVertices, sizeof(squareVertices));

		{
			BufferLayout squareVBOLayout = {
				{ ShaderDataType::Float3, "a_Position" },
				{ ShaderDataType::Float2, "a_TextureCoord" }
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

		s_Renderer2DData->WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Renderer2DData->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		s_Renderer2DData->TextureShader = Shader::Create("assets/shaders/Texture.glsl");
		s_Renderer2DData->TextureShader->Bind();
		s_Renderer2DData->TextureShader->SetInt("u_Texture", 0);
	}

	void Renderer2D::Shutdown()
	{
		delete s_Renderer2DData;
	}

	void Renderer2D::BeginScene(const SharedPtr<CameraBase>& camera)
	{
		s_Renderer2DData->TextureShader->Bind();
		s_Renderer2DData->TextureShader->SetMat4("u_ViewProjection", camera->GetViewProjectionMatrix());
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
		s_Renderer2DData->TextureShader->SetFloat4("u_Color", color);
		s_Renderer2DData->WhiteTexture->Bind();
		
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
			glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
		s_Renderer2DData->TextureShader->SetMat4("u_Transform", transform);

		s_Renderer2DData->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Renderer2DData->QuadVertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const SharedPtr<Texture2D>& texture)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const SharedPtr<Texture2D>& texture)
	{
		s_Renderer2DData->TextureShader->SetFloat4("u_Color", glm::vec4(1.0f));
		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Renderer2DData->TextureShader->SetMat4("u_Transform", transform);

		s_Renderer2DData->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Renderer2DData->QuadVertexArray);
	}

}