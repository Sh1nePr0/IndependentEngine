#include "Application.h"

#include "Independent/Events/ApplicationEvent.h"
#include "Independent/Log.h"

namespace Independent {

	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run() 
	{
		WindowResizeEvent e(1280, 720);
		IDPD_TRACE(e.ToString());

		while (true);
	}
}


