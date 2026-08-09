#include <ForgeQt/UI/EditorWindow.h>

#include "Backend/Qt/EditorWindowBackend.h"

#include <memory>
#include <utility>

namespace Forge::UI
{
    EditorWindow::EditorWindow()
        : m_Backend(
            std::make_unique<Backend::Qt::EditorWindowBackend>())
    {}

    EditorWindow::~EditorWindow() = default;

    EditorWindow::EditorWindow(EditorWindow&&) noexcept = default;

    EditorWindow& EditorWindow::operator=(EditorWindow&&) noexcept = default;

    void EditorWindow::Show()
    {
        m_Backend->Show();
    }

    void EditorWindow::Close()
    {
        m_Backend->Close();
    }

    void EditorWindow::SetTitle(const std::string& title)
    {
        m_Backend->SetTitle(title);
    }

    void EditorWindow::SetSize(int width, int height)
    {
        m_Backend->SetSize(width, height);
    }

    void EditorWindow::SetCentralPlaceholder(const std::string& title)
    {
        m_Backend->SetCentralPlaceholder(title);
    }

    void EditorWindow::AddDockPanel(const std::string& id, const std::string& title, DockArea area)
    {
        m_Backend->AddDockPanel(id, title, area);
    }

    void EditorWindow::AddMenu(const std::string& id, const std::string& title)
    {
        m_Backend->AddMenu(id, title);
    }

    void EditorWindow::AddMenuAction(const std::string& menuId, const std::string& title, ActionCallback callback)
    {
        m_Backend->AddMenuAction(menuId, title, std::move(callback));
    }
}