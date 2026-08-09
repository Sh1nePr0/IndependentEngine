#include <ForgeQt/Core/Application.h>
#include <ForgeQt/UI/EditorWindow.h>

int main(int argc, char** argv)
{
	Forge::Core::Application application(argc, argv);

	Forge::UI::EditorWindow editorWindow;
	editorWindow.SetTitle("Forge Editor");
	editorWindow.SetSize(1280, 720);

    editorWindow.SetCentralPlaceholder("Viewport");

    editorWindow.AddDockPanel(
        "HierarchyPanel",
        "Hierarchy",
        Forge::UI::DockArea::Left);

    editorWindow.AddDockPanel(
        "InspectorPanel",
        "Inspector",
        Forge::UI::DockArea::Right);

    editorWindow.AddDockPanel(
        "ConsolePanel",
        "Console",
        Forge::UI::DockArea::Bottom);

    editorWindow.AddMenu("FileMenu", "&File");
    editorWindow.AddMenu("EditMenu", "&Edit");
    editorWindow.AddMenu("ViewMenu", "&View");
    editorWindow.AddMenu("HelpMenu", "&Help");

    editorWindow.AddMenuAction(
        "FileMenu",
        "Exit",
        [&editorWindow]()
        {
            editorWindow.Close();
        });

	editorWindow.Show();

	return application.Execute();
}