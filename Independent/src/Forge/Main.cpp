#include "Platform/Direct3D12/include/Direct3D12Device.h"
#include "Platform/Direct3D12/include/Direct3D12CommandContext.h"

#include <exception>
#include <iostream>

#include <ForgeQt/Core/Application.h>
#include <ForgeQt/UI/EditorWindow.h>

int main(int argc, char** argv)
{
    try
    {
        Independent::Direct3D12Device device;
        Independent::Direct3D12CommandContext commandContext(device);

        for (unsigned int iteration = 0; iteration < 3; ++iteration)
        {
            commandContext.BeginRecording();

            commandContext.EndRecording();

            ID3D12CommandList* commandLists[] =
            {
                commandContext.GetCommandList()
            };

            device.GetGraphicsQueue()->ExecuteCommandLists(
                1,
                commandLists);

            device.WaitForGraphicsQueue();

            std::cout
                << "Submission " << iteration + 1
                << " completed.\n";
        }
        
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }

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