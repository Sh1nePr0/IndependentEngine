#include <Independent.h>
#include <ImGui/imgui.h>

class ExampleLayer : public Independent::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
		m_Camera = std::make_shared<Independent::OrthographicCamera>(-1.6f, 1.6f, -0.9f, 0.9f);

		m_CameraPosition = { 0.0f, 0.0f, 0.0f };

		m_VertexArray.reset(Independent::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		Independent::SharedPtr<Independent::VertexBuffer> triangleVBO;
		triangleVBO.reset(Independent::VertexBuffer::Create(vertices, sizeof(vertices)));

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
		triangleIBO.reset(Independent::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(triangleIBO);

		m_SquareVAO.reset(Independent::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		Independent::SharedPtr<Independent::VertexBuffer> squareVBO;
		squareVBO.reset(Independent::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		{
			Independent::BufferLayout squareVBOLayout = {
				{ Independent::ShaderDataType::Float3, "a_Position" }
			};

			squareVBO->SetLayout(squareVBOLayout);
		}

		m_SquareVAO->AddVertexBuffer(squareVBO);

		uint32_t squareIndices[6] = {
			0, 1 , 2 , 2, 3 ,0
		};

		Independent::SharedPtr<Independent::IndexBuffer> squareIBO;
		squareIBO.reset(Independent::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVAO->SetIndexBuffer(squareIBO);

		Independent::String vertexSrc = R"(
			#version 330 core
		
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
	
			out vec3 v_Position;
			out vec4 v_Color;
	
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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

		m_Shader.reset(new Independent::Shader(vertexSrc, fragmentSrc));

		Independent::String blueShaderVertexSrc = R"(
			#version 330 core
		
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
	
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}	
		)";

		Independent::String blueShaderFragmentSrc = R"(
			#version 330 core
		
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
	
			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}	
		)";

		m_BlueShader.reset(new Independent::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
	}

	void OnUpdate() override
	{
		if (Independent::Input::IsKeyPressed(IDPD_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed;
		else if (Independent::Input::IsKeyPressed(IDPD_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed;

		if (Independent::Input::IsKeyPressed(IDPD_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed;
		else if (Independent::Input::IsKeyPressed(IDPD_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed;

		if (Independent::Input::IsKeyPressed(IDPD_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed;

		if (Independent::Input::IsKeyPressed(IDPD_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed;

		Independent::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Independent::RenderCommand::Clear();

		Independent::CameraManager::AddCamera("Ortho", m_Camera);
		Independent::CameraManager::SetActiveCamera("Ortho");

		m_Camera->SetPosition(m_CameraPosition);
		m_Camera->SetRotation(m_CameraRotation);

		Independent::Renderer::BeginScene(m_Camera);

		Independent::Renderer::Submit(m_BlueShader, m_SquareVAO);
		Independent::Renderer::Submit(m_Shader, m_VertexArray);

		Independent::Renderer::EndScene();
	}

	virtual void OnImGuiRenderer() override
	{
		
	}

	void OnEvent(Independent::Event& event) override
	{
		
	}

	
private:
	Independent::SharedPtr<Independent::Shader> m_Shader;
	Independent::SharedPtr<Independent::VertexArray> m_VertexArray;

	Independent::SharedPtr<Independent::Shader> m_BlueShader;
	Independent::SharedPtr<Independent::VertexArray> m_SquareVAO;

	Independent::SharedPtr<Independent::OrthographicCamera> m_Camera;

	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 0.1f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 2.0f;
};

class IndependentEditor : public Independent::Application
{
public:
	IndependentEditor()
	{
		PushLayer(new ExampleLayer());
	}

	~IndependentEditor()
	{

	}


};

Independent::Application* Independent::CreateApplication()
{
	return new IndependentEditor();
}
