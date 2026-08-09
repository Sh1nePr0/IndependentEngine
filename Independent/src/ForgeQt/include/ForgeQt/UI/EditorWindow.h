#pragma once

#include <ForgeQt/UI/DockArea.h>

#include <functional>
#include <memory>
#include <string>

namespace Forge::Backend::Qt
{
	class EditorWindowBackend;
}

namespace Forge::UI
{
	class EditorWindow
	{
	public:
		using ActionCallback = std::function<void()>;

		EditorWindow();
		~EditorWindow();

		EditorWindow(const EditorWindow&) = delete;
		EditorWindow& operator=(const EditorWindow&) = delete;

		EditorWindow(EditorWindow&&) noexcept;
		EditorWindow& operator=(EditorWindow&&) noexcept;

		void Show();
		void Close();

		void SetTitle(const std::string& title);
		void SetSize(int width, int height);

		void SetCentralPlaceholder(const std::string& title);

		void AddDockPanel(
			const std::string& id,
			const std::string& title,
			DockArea area);

		void AddMenu(
			const std::string& id,
			const std::string& title);

		void AddMenuAction(
			const std::string& menuId,
			const std::string& title,
			ActionCallback callback);

	private:
		std::unique_ptr<Backend::Qt::EditorWindowBackend> m_Backend;
	};
}