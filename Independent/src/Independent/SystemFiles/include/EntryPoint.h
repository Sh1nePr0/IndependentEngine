#pragma once

#ifdef IDPD_PLATFORM_WINDOWS

extern Independent::Application* Independent::CreateApplication();

int main(int argc, char** argv)
{
	Independent::Log::Init();
	IDPD_CORE_WARNING("Initialized Log!");
	int a = 5;
	IDPD_INFO("Hello! Var={0}", a);
	
	auto app = Independent::CreateApplication();
	app->Run();
	delete app;
}

#endif