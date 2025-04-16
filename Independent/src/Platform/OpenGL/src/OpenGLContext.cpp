#include "idpdpch.h"
#include "Platform/OpenGL/include/OpenGLContext.h"

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
		IDPD_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		IDPD_CORE_ASSERT(status, "Failed to initialize Glad!");

		IDPD_CORE_INFO(" OpenGL Info:");
		IDPD_CORE_INFO(" Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		IDPD_CORE_INFO(" Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		IDPD_CORE_INFO(" Version: {0}", (const char*)glGetString(GL_VERSION));

		#ifdef IDPD_ENABLE_ASSERTS
			int versionMajor;
			int versionMinor;
			glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
			glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

			IDPD_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Independent Engine requires at least OpenGL version 4.5!");
		#endif
	}

	void OpenGLContext::SwapBuffers()
	{
		IDPD_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}

}
