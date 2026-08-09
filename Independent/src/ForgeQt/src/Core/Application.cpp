#include <ForgeQt/Core/Application.h>
#include "Backend/Qt/ApplicationBackend.h"

namespace Forge::Core
{
	Application::Application(int argc, char** argv)
		: m_Backend(std::make_unique<Backend::Qt::ApplicationBackend>(argc, argv))
	{}

	Application::~Application() = default;

	int Application::Execute()
	{
		return m_Backend->Execute();
	}
}