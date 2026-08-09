#pragma once

#include <ForgeQt/UI/DockArea.h>

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

class QDockWidget;
class QMainWindow;
class QMenu;

namespace Forge::Backend::Qt
{
	class EditorWindowBackend
	{
	public:
		using ActionCallback = std::function<void()>;

		EditorWindowBackend();
		~EditorWindowBackend();

		EditorWindowBackend(const EditorWindowBackend&) = delete;
		EditorWindowBackend& operator=(const EditorWindowBackend&) = delete;

		void Show();
		void Close();

		void SetTitle(const std::string& title);
		void SetSize(int width, int height);

		void SetCentralPlaceholder(const std::string& title);

		void AddDockPanel(
			const std::string& id,
			const std::string& title,
			UI::DockArea area);

		void AddMenu(
			const std::string& id,
			const std::string& title);

		void AddMenuAction(
			const std::string& menuId,
			const std::string& title,
			ActionCallback callback);

	private:
		std::unique_ptr<QMainWindow> m_Window;

		std::unordered_map<std::string, QMenu*> m_Menus;
		std::unordered_map<std::string, QDockWidget*> m_DockPanels;
	};
}