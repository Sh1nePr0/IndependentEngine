#pragma once

#include "Independent/Window.h"
#include "Independent/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace Independent {

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowsProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }
		
		//Attributes
		inline void SetEventCallback(const EventCallbackFunction& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		inline virtual void* GetNativeWindow() const { return m_Window; }
	private:
		virtual void Init(const WindowsProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* m_Window;
		GraphicsContext* m_Context;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool bVSync;

			EventCallbackFunction EventCallback;
		};

		WindowData m_Data;
	};
}