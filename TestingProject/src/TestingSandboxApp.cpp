#include <Independent.h>
#include <Independent/SystemFiles/include/EntryPoint.h>
#include <ImGui/imgui.h>

#include "Platform/OpenGL/include/OpenGLShader.h"
#include <glm/gtc/type_ptr.hpp>

#include "TestingSandbox2D.h"

class ExampleLayer : public Independent::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(1280.0f / 720.f, true)
	{
		m_VertexArray = Independent::VertexArray::Create();

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		Independent::SharedPtr<Independent::VertexBuffer> triangleVBO;
		triangleVBO = Independent::VertexBuffer::Create(vertices, sizeof(vertices));

		{
			Independent::BufferLayout triangleVBOLayout = {
				{ Independent::ShaderDataType::Float3, "a_Position" },
				{ Independent::ShaderDataType::Float4, "a_Color"}
			};

			triangleVBO->SetLayout(triangleVBOLayout);
		}

		m_VertexArray->AddVertexBuffer(triangleVBO);

		uint32_t indices[3] = {
			0, 1 , 2
		};

		Independent::SharedPtr<Independent::IndexBuffer> triangleIBO;
		triangleIBO = Independent::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		m_VertexArray->SetIndexBuffer(triangleIBO);

		m_SquareVAO = Independent::VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Independent::SharedPtr<Independent::VertexBuffer> squareVBO;
		squareVBO = Independent::VertexBuffer::Create(squareVertices, sizeof(squareVertices));

		{
			Independent::BufferLayout squareVBOLayout = {
				{ Independent::ShaderDataType::Float3, "a_Position" },
				{ Independent::ShaderDataType::Float2, "a_TextureCoord" }
			};

			squareVBO->SetLayout(squareVBOLayout);
		}

		m_SquareVAO->AddVertexBuffer(squareVBO);

		uint32_t squareIndices[6] = {
			0, 1 , 2 , 2, 3 ,0
		};

		Independent::SharedPtr<Independent::IndexBuffer> squareIBO;
		squareIBO = Independent::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		m_SquareVAO->SetIndexBuffer(squareIBO);

		Independent::String vertexSrc = R"(
			#version 330 core
		
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
	
			out vec3 v_Position;
			out vec4 v_Color;
	
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}	
		)";

		Independent::String fragmentSrc = R"(
			#version 330 core
		
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;
	
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;	
			}	
		)";

		m_Shader = Independent::Shader::Create("baseShader", vertexSrc, fragmentSrc);

		Independent::String flatColorShaderVertexSrc = R"(
			#version 330 core
		
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
	
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}	
		)";

		Independent::String flatColorShaderFragmentSrc = R"(
			#version 330 core
		
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;
	
			void main()
			{
				color = vec4(u_Color, 1.0);
			}	
		)";

		m_FlatColorShader = Independent::Shader::Create("flatColorShader", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = Independent::Texture2D::Create("assets/textures/witcherLogo.png");

		std::dynamic_pointer_cast<Independent::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Independent::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);

	}

	void OnUpdate(Independent::Timestep ts) override
	{
		// Update 
		m_CameraController.OnUpdate(ts);

		// Render
		Independent::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Independent::RenderCommand::Clear();

		Independent::Renderer::BeginScene(std::make_shared<Independent::OrthographicCamera>(m_CameraController.GetCamera()));
		
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Independent::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Independent::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;

				Independent::Renderer::Submit(m_FlatColorShader, m_SquareVAO, transform);
			}
		}

		auto textureShader = m_ShaderLibrary.Get("Texture");
		
		m_Texture->Bind();
		Independent::Renderer::Submit(
			textureShader,
			m_SquareVAO, 
			glm::scale(glm::mat4(1.0f), glm::vec3(1.7f, 1.0f, 1.0f))
		);

		// Triangle
		//Independent::Renderer::Submit(m_Shader, m_VertexArray);

		Independent::Renderer::EndScene();
	}

	virtual void OnImGuiRenderer() override
	{
		ImGui::Begin("Settings");

		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));

		ImGui::End();
	}

	void OnEvent(Independent::Event& e) override
	{
		m_CameraController.OnEvent(e);
	}

	
private:
	Independent::ShaderLibrary m_ShaderLibrary;
	Independent::SharedPtr<Independent::Shader> m_Shader;
	Independent::SharedPtr<Independent::VertexArray> m_VertexArray;

	Independent::SharedPtr<Independent::Shader> m_FlatColorShader;
	Independent::SharedPtr<Independent::VertexArray> m_SquareVAO;

	Independent::SharedPtr<Independent::Texture2D> m_Texture;

	Independent::OrthographicCameraController m_CameraController;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class TestingSandbox : public Independent::Application
{
public:
	TestingSandbox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new TestingSandbox2D());
	}

	~TestingSandbox()
	{

	}


};

Independent::Application* Independent::CreateApplication()
{
	return new TestingSandbox();
}
