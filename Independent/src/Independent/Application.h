#pragma once

#include "Independent/SystemFiles/include/Core.h"

#include "Independent/SystemFiles/include/Window.h"
#include "Independent/SystemFiles/include/LayerStack.h"
#include "Independent/SystemFiles/include/Events/Event.h"
#include "Independent/SystemFiles/include/Events/ApplicationEvent.h"

#include "Independent/SystemFiles/include/ImGui/ImGuiLayer.h"

#include "Independent/Core/include/containers/UniquePtr.h"
#include "Independent/Core/include/containers/SharedPtr.h"

namespace Independent {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		
		inline Window& GetWindow() const { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		UniquePtr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}


