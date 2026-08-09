#include "EditorWindowBackend.h"

#include <QAction>
#include <QDockWidget>
#include <QFrame>
#include <QLabel>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QObject>
#include <QString>
#include <QVBoxLayout>
#include <QWidget>

#include <memory>
#include <utility>

namespace
{
	::Qt::DockWidgetArea ToQtDockArea(
		Forge::UI::DockArea area)
	{
		switch (area)
		{
		case Forge::UI::DockArea::Left:
			return ::Qt::LeftDockWidgetArea;
		case Forge::UI::DockArea::Right:
			return ::Qt::RightDockWidgetArea;
		case Forge::UI::DockArea::Top:
			return ::Qt::TopDockWidgetArea;
		case Forge::UI::DockArea::Bottom:
			return ::Qt::BottomDockWidgetArea;
		}

		return ::Qt::LeftDockWidgetArea;
	}
}

namespace Forge::Backend::Qt
{
	EditorWindowBackend::EditorWindowBackend()
		: m_Window(std::make_unique<QMainWindow>())
	{
		m_Window->setWindowTitle(QStringLiteral("Forge"));
		m_Window->resize(1280, 720);

		m_Window->setDockOptions(
			QMainWindow::AnimatedDocks |
			QMainWindow::AllowNestedDocks |
			QMainWindow::AllowTabbedDocks);

		m_Window->setDockNestingEnabled(true);
	}

	EditorWindowBackend::~EditorWindowBackend() = default;

	void EditorWindowBackend::Show()
	{
		m_Window->show();
	}

	void EditorWindowBackend::Close()
	{
		m_Window->close();
	}

	void EditorWindowBackend::SetTitle(const std::string& title)
	{
		m_Window->setWindowTitle(QString::fromStdString(title));
	}

	void EditorWindowBackend::SetSize(int width, int height)
	{
		if (width <= 0 || height <= 0)
		{
			return;
		}

		m_Window->resize(width, height);
	}

	void EditorWindowBackend::SetCentralPlaceholder(const std::string& title)
	{
		auto* centralWidget = new QFrame(m_Window.get());

		centralWidget->setObjectName(QStringLiteral("ForgeCentralArea"));
		centralWidget->setFrameShape(QFrame::StyledPanel);

		auto* layout = new QVBoxLayout(centralWidget);

		layout->setContentsMargins(0, 0, 0, 0);

		auto* label = new QLabel(QString::fromStdString(title), centralWidget);

		label->setAlignment(::Qt::AlignCenter);

		layout->addWidget(label);

		m_Window->setCentralWidget(centralWidget);
	}

	void EditorWindowBackend::AddDockPanel(const std::string& id, const std::string& title, UI::DockArea area)
	{
		if (m_DockPanels.find(id) != m_DockPanels.end())
		{
			return;
		}

		auto* dockWidget = new QDockWidget(QString::fromStdString(title), m_Window.get());

		dockWidget->setObjectName(QString::fromStdString(id));
		dockWidget->setAllowedAreas(
			::Qt::LeftDockWidgetArea |
			::Qt::RightDockWidgetArea |
			::Qt::TopDockWidgetArea |
			::Qt::BottomDockWidgetArea);

		auto* contentWidget = new QWidget(dockWidget);
		auto* layout = new QVBoxLayout(contentWidget);

		auto* label = new QLabel(QString::fromStdString(title), contentWidget);
		label->setAlignment(::Qt::AlignCenter);

		layout->addWidget(label);

		dockWidget->setWidget(contentWidget);

		m_Window->addDockWidget(ToQtDockArea(area), dockWidget);

		m_DockPanels.emplace(id, dockWidget);
	}

	void EditorWindowBackend::AddMenu(const std::string& id, const std::string& title)
	{
		if (m_Menus.find(id) != m_Menus.end())
		{
			return;
		}

		QMenu* menu = m_Window->menuBar()->addMenu(
			QString::fromStdString(title));

		m_Menus.emplace(id, menu);
	}

	void EditorWindowBackend::AddMenuAction(const std::string& menuId, const std::string& title, ActionCallback callback)
	{
		const auto iterator = m_Menus.find(menuId);

		if (iterator == m_Menus.end())
		{
			return;
		}

		QMenu* menu = iterator->second;

		QAction* action = menu->addAction(
			QString::fromStdString(title));

		QObject::connect(
			action,
			&QAction::triggered,
			[callback = std::move(callback)]() mutable
			{
				if (callback)
				{
					callback();
				}
			});
	}
}