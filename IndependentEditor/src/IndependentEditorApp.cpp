#include <Independent.h>

class ExampleLayer : public Independent::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{

	}

	void OnUpdate() override
	{
		IDPD_INFO("ExampleLayer::Update");
	}

	void OnEvent(Independent::Event& event) override
	{
		IDPD_TRACE("{0}", event.ToString());
	}
};

class IndependentEditor : public Independent::Application
{
public:
	IndependentEditor()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Independent::ImGuiLayer());
	}

	~IndependentEditor()
	{

	}


};

Independent::Application* Independent::CreateApplication()
{
	return new IndependentEditor();
}
