#include "idpdpch.h"
#include "Application.h"

#include "Independent/Log.h"

#include <glad/glad.h>

#include "Input.h"

namespace Independent {

#define BIND_EVENT_FUNCTION(x) std::bind(&x, this, std::placeholders::_1)\

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		IDPD_CORE_ASSERT(!s_Instance, "Application already exist!");
		s_Instance = this;

		m_Window =  std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FUNCTION(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		m_VertexArray.reset(VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<VertexBuffer> triangleVBO;
		triangleVBO.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		{
			BufferLayout triangleVBOLayout = {
				{ ShaderDataType::Float3, "a_Position" },
				{ ShaderDataType::Float4, "a_Color"}
			};

			triangleVBO->SetLayout(triangleVBOLayout);
		}

		m_VertexArray->AddVertexBuffer(triangleVBO);
		
		uint32_t indices[3] = {
			0, 1 , 2
		};

		std::shared_ptr<IndexBuffer> triangleIBO;
		triangleIBO.reset(IndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(triangleIBO);

		m_SquareVAO.reset(VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<VertexBuffer> squareVBO;
		squareVBO.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		{
			BufferLayout squareVBOLayout = {
				{ ShaderDataType::Float3, "a_Position" }
			};

			squareVBO->SetLayout(squareVBOLayout);
		}

		m_SquareVAO->AddVertexBuffer(squareVBO);

		uint32_t squareIndices[6] = {
			0, 1 , 2 , 2, 3 ,0
		};

		std::shared_ptr<IndexBuffer> squareIBO;
		squareIBO.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices)/sizeof(uint32_t)));
		m_SquareVAO->SetIndexBuffer(squareIBO);

		std::string vertexSrc = R"(
			#version 330 core
		
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
	
			out vec3 v_Position;
			out vec4 v_Color;
	
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);
			}	
		)";

		std::string fragmentSrc = R"(
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

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));

		std::string blueShaderVertexSrc = R"(
			#version 330 core
		
			layout(location = 0) in vec3 a_Position;
	
			out vec3 v_Position;
	
			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
			}	
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core
		
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
	
			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}	
		)";

		m_BlueShader.reset(new Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
	}

	Application::~Application()
	{

	}

	void Application::Run() 
	{
		while (m_Running)
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_BlueShader->Bind();
			m_SquareVAO->Bind();
			glDrawElements(GL_TRIANGLES, m_SquareVAO->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			m_Shader->Bind();
			m_VertexArray->Bind();
			glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
			{
				layer->OnImGuiRenderer();
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNCTION(Application::OnWindowClose));

		IDPD_CORE_TRACE("{0}", e.ToString());

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled())
			{
				break;
			}
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}


