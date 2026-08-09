#pragma once

#include <memory>

class QApplication;

namespace Forge::Backend::Qt
{
    class ApplicationBackend
    {
    public:
        ApplicationBackend(int argc, char** argv);
        ~ApplicationBackend();

        ApplicationBackend(const ApplicationBackend&) = delete;
        ApplicationBackend& operator=(const ApplicationBackend&) = delete;

        int Execute();

    private:
        std::unique_ptr<QApplication> m_Application;
    };
}