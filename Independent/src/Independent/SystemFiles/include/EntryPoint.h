#pragma once

#ifdef IDPD_PLATFORM_WINDOWS

extern Independent::Application* Independent::CreateApplication();

int main(int argc, char** argv)
{
	Independent::Log::Init();
	
	IDPD_PROFILE_BEGIN_SESSION("Startup", "IndependentProfile-Startup.json");
	auto app = Independent::CreateApplication();
	IDPD_PROFILE_END_SESSION();

	IDPD_PROFILE_BEGIN_SESSION("Runtime", "IndependentProfile-Runtime.json");
	app->Run();
	IDPD_PROFILE_END_SESSION();

	IDPD_PROFILE_BEGIN_SESSION("Shutdown", "IndependentProfile-Shutdown.json");
	delete app;
	IDPD_PROFILE_END_SESSION();
}

#endif