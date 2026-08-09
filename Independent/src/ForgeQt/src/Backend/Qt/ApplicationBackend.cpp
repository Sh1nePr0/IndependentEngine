#include "ApplicationBackend.h"

#include <QApplication>
#include <QCoreApplication>

#include <memory>

namespace Forge::Backend::Qt
{
    ApplicationBackend::ApplicationBackend(int argc, char** argv)
        : m_Application(std::make_unique<QApplication>(argc, argv))
    {
        QCoreApplication::setApplicationName("Forge");
        QCoreApplication::setOrganizationName("Independent Engine");
    }

    ApplicationBackend::~ApplicationBackend() = default;

    int ApplicationBackend::Execute()
    {
        return m_Application->exec();
    }
}