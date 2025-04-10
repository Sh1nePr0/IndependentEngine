#include "idpdpch.h"
#include "Application.h"

#include "Independent/SystemFiles/include/Log.h"
#include "Independent/SystemFiles/include/Input.h"

#include "Render/include/Renderer.h"

#include "Independent/Core/include/containers/String.h"

#include <glfw/glfw3.h>

namespace Independent {

#define BIND_EVENT_FUNCTION(x) std::bind(&x, this, std::placeholders::_1)\

	Application* Application::s_Instance = nullptr;

	Application::Application()
		
	{
		IDPD_CORE_ASSERT(!s_Instance, "Application already exist!");
		s_Instance = this;

		m_Window = UniquePtr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FUNCTION(Application::OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{

	}

	void Application::Run() 
	{
		while (m_Running)
		{
			float time = (float)glfwGetTime(); // TODO: Should be something like Platform::GetTime()

			Timestep timestep = time - m_LastFrameTime; 
			m_LastFrameTime = time;

			if (!m_Minimazed)
			{
				for (Layer* layer : m_LayerStack)
				{
					layer->OnUpdate(timestep);
				}
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
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FUNCTION(Application::OnWindowResize));

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

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimazed = true;
			return false;
		}

		m_Minimazed = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}

}


