#include "idpdpch.h"
#include "Platform/Windows/include/WindowsWindow.h"

#include "Independent/SystemFiles/include/Events/ApplicationEvent.h"
#include "Independent/SystemFiles/include/Events/MouseEvent.h"
#include "Independent/SystemFiles/include/Events/KeyEvent.h"

#include "Platform/OpenGL/include/OpenGLContext.h"

namespace Independent {

	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* msg)
	{
		IDPD_CORE_ERROR("GLFW Error ({0}): {1}", error, msg);
	}

	UniquePtr<Window> Window::Create(const WindowsProps& props)
	{
		return std::make_unique<WindowsWindow>(props);
	}

	WindowsWindow::WindowsWindow(const WindowsProps& props)
	{
		IDPD_PROFILE_FUNCTION();

		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		IDPD_PROFILE_FUNCTION();

		Shutdown();
	}

	void WindowsWindow::Init(const WindowsProps& props)
	{
		IDPD_PROFILE_FUNCTION();

		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;
		
		IDPD_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);


		if (!s_GLFWInitialized)
		{
			//TODO: glfwTerminate on system shutdown
			IDPD_PROFILE_SCOPE("glfwInit");
			int success = glfwInit();
			IDPD_CORE_ASSERT(success, "Could bot initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		{
			IDPD_PROFILE_SCOPE("glfwCreateWindow");
			m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		}

		m_Context = new OpenGLContext(m_Window);
		m_Context->Init();

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		//Set GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;

				WindowResizeEvent event(width, height);
				data.EventCallback(event);
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.EventCallback(event);
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
					case GLFW_PRESS:
					{
						KeyPressedEvent event(key, 0);
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleasedEvent event(key);
						data.EventCallback(event);
						break;
					}
					case GLFW_REPEAT:
					{
						KeyPressedEvent event(key, 1);
						data.EventCallback(event);
						break;
					}
				}
			});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				KeyTypedEvent event(keycode);
				data.EventCallback(event);
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
					case GLFW_PRESS: 
					{
						MouseButtonPressedEvent event(button);
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent event(button);
						data.EventCallback(event);
						break;
					}
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event((float)xoffset, (float)yoffset);
				data.EventCallback(event);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)xpos, (float)ypos);
				data.EventCallback(event);
			});
	}

	void WindowsWindow::Shutdown()
	{
		IDPD_PROFILE_FUNCTION();

		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		IDPD_PROFILE_FUNCTION();

		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		IDPD_PROFILE_FUNCTION();

		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.bVSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.bVSync;
	}

}
