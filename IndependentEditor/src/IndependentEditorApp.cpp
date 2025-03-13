#include <Independent.h>
#include <ImGui/imgui.h>

class ExampleLayer : public Independent::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{

	}

	void OnUpdate() override
	{
		if (Independent::Input::IsKeyPressed(IDPD_KEY_TAB))
			IDPD_INFO("Tab key is pressed! (poll)");
	}

	virtual void OnImGuiRenderer() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void OnEvent(Independent::Event& event) override
	{
		if (event.GetEventType() == Independent::EventType::KeyPressed)
		{
			Independent::KeyPressedEvent& e = (Independent::KeyPressedEvent&)event;
			if (e.GetKeyCode() == IDPD_KEY_TAB)
				IDPD_TRACE("Tab key is pressed! (event)");
			IDPD_TRACE("{0}", (char)e.GetKeyCode());
		}
		
	}
};

class IndependentEditor : public Independent::Application
{
public:
	IndependentEditor()
	{
		PushLayer(new ExampleLayer());
	}

	~IndependentEditor()
	{

	}


};

Independent::Application* Independent::CreateApplication()
{
	return new IndependentEditor();
}
