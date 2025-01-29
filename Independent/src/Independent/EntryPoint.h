#pragma once

#ifdef IDPD_PLATFORM_WINDOWS

extern Independent::Application* Independent::CreateApplication();

int main(int argc, char** argv)
{
	printf("Independent Engine!\n");
	auto app = Independent::CreateApplication();
	app->Run();
	delete app;
}

#endif