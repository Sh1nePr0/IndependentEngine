#include "idpdpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Independent {

	
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		IDPD_CORE_ASSERT(windowHandle, "Window handle is nullptr!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		IDPD_CORE_ASSERT(status, "Failed to initialize Glad!");

		IDPD_CORE_INFO(" OpenGL Info:");
		IDPD_CORE_INFO(" Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		IDPD_CORE_INFO(" Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		IDPD_CORE_INFO(" Version: {0}", (const char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}
