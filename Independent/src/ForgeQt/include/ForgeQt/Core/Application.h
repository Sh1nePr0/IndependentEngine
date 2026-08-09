#pragma once

#include <memory>

namespace Forge::Backend::Qt 
{
    class ApplicationBackend;
}

namespace Forge::Core
{
    class Application 
    {
    public:
        Application(int argc, char** argv);
        ~Application();

        Application(const Application&) = delete;
        Application& operator=(const Application&) = delete;

        Application(Application&&) = delete;
        Application& operator=(Application&&) = delete;

        int Execute();

    private:
        std::unique_ptr<Backend::Qt::ApplicationBackend> m_Backend;
    };
}