#pragma once

#include "Independent/SystemFiles/include/Core.h"

#include "Independent/SystemFiles/include/Window.h"
#include "Independent/SystemFiles/include/LayerStack.h"
#include "Independent/SystemFiles/include/Events/Event.h"
#include "Independent/SystemFiles/include/Events/ApplicationEvent.h"

#include "Independent/SystemFiles/include/ImGui/ImGuiLayer.h"

#include "Render/include/shader/Shader.h"
#include "Render/include/buffer/Buffer.h"
#include "Render/include/vertex_array/VertexArray.h"

namespace Independent {

	class INDEPENDENT_API Application
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

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<Shader> m_BlueShader;
		std::shared_ptr<VertexArray> m_SquareVAO;
	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}


