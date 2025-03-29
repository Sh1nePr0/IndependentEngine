#pragma once

#include "idpdpch.h"

#include "Independent/SystemFiles/include/Core.h"
#include "Independent/SystemFiles/include/Events/Event.h"
#include "Independent/Core/include/containers/String.h"

namespace Independent {

	struct WindowsProps
	{
		String Title;
		unsigned int Width;
		unsigned int Height;

		WindowsProps(const String& title = "Independent Engine",
					 unsigned int width = 1280,
					 unsigned int height = 720)
			:Title(title), Width(width), Height(height)
		{

		}
	};

	//Interface that representing a desktop system based Window
	class INDEPENDENT_API Window
	{
	public:
		using EventCallbackFunction = std::function<void(Event&)>;

		virtual  ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		//Attributes for window
		virtual void SetEventCallback(const EventCallbackFunction& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowsProps& props = WindowsProps());
	};

}