#include "idpdpch.h"
#include "Application.h"

#include "Independent/SystemFiles/include/Log.h"
#include "Independent/SystemFiles/include/Input.h"

#include "Render/include/Renderer.h"

#include "Independent/Core/include/containers/String.h"

#include <glfw/glfw3.h>

namespace Independent {

	Application* Application::s_Instance = nullptr;

	Application::Application()	
	{
		IDPD_PROFILE_FUNCTION();

		IDPD_CORE_ASSERT(!s_Instance, "Application already exist!");
		s_Instance = this;

		m_Window = UniquePtr<Window>(Window::Create());
		m_Window->SetEventCallback(IDPD_BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{
		IDPD_PROFILE_FUNCTION();

		Renderer::Shutdown();
	}

	void Application::Run() 
	{
		IDPD_PROFILE_FUNCTION();

		while (m_Running)
		{
			IDPD_PROFILE_SCOPE("RunLoop");

			float time = (float)glfwGetTime(); // TODO: Should be something like Platform::GetTime()

			Timestep timestep = time - m_LastFrameTime; 
			m_LastFrameTime = time;

			if (!m_Minimazed)
			{
				{
					IDPD_PROFILE_SCOPE("LayerStack: OnUpdate");

					for (Layer* layer : m_LayerStack)
					{
						layer->OnUpdate(timestep);
					}
				}

				m_ImGuiLayer->Begin();
				{
					IDPD_PROFILE_SCOPE("LayerStack: OnImGuiRender");
					for (Layer* layer : m_LayerStack)
					{
						layer->OnImGuiRender();
					}
				}
				m_ImGuiLayer->End();
			}

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		IDPD_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(IDPD_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(IDPD_BIND_EVENT_FN(Application::OnWindowResize));

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
		IDPD_PROFILE_FUNCTION();

		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		IDPD_PROFILE_FUNCTION();

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
		IDPD_PROFILE_FUNCTION();

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


