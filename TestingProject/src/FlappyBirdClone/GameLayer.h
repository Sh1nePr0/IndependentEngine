#pragma once

#include <Independent.h>

#include "Level.h"
#include <imgui/imgui.h>

class GameLayer : public Independent::Layer
{
public:
	GameLayer();
	virtual ~GameLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Independent::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Independent::Event& e) override;
	bool OnMouseButtonPressed(Independent::MouseButtonPressedEvent& e);
	bool OnWindowResize(Independent::WindowResizeEvent& e);
private:
	void CreateCamera(uint32_t width, uint32_t height);
private:
	Independent::SharedPtr<Independent::OrthographicCamera> m_Camera;
	Level m_Level;
	ImFont* m_Font;
	float m_Time = 0.0f;
	bool m_Blink = false;

	enum class GameState
	{
		Play = 0,
		MainMenu = 1,
		GameOver = 2
	};

	GameState m_State = GameState::MainMenu;
};