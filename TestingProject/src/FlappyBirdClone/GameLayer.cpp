#include <ImGui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

#include "GameLayer.h"


GameLayer::GameLayer()
	: Layer("GameLayer")
{
	auto& window = Independent::Application::Get().GetWindow();
	CreateCamera(window.GetWidth(), window.GetHeight());

	Random::Init();
}

void GameLayer::OnAttach()
{
	m_Level.Init();

	ImGuiIO io = ImGui::GetIO();
	m_Font = io.Fonts->AddFontFromFileTTF("assets/fonts/Delius-Regular.ttf", 120.0f);
}

void GameLayer::OnDetach()
{
	
}

void GameLayer::OnUpdate(Independent::Timestep ts)
{
	m_Time += ts;
	if ((int)(m_Time * 10.0f) % 8 > 4)
		m_Blink = !m_Blink;

	if (m_Level.IsGameOver())
		m_State = GameState::GameOver;  

	const glm::vec2& playerPos = m_Level.GetPlayer().GetPosition();
	m_Camera->SetPosition({ playerPos.x, playerPos.y, 0.0f });

	switch (m_State)
	{
		case GameState::Play:
		{
			m_Level.OnUpdate(ts);
			break;
		}
	}

	
	//Render
 	Independent::RenderCommand::SetClearColor({ 0.0f, 0.0f, 0.0f, 1.0f });
	Independent::RenderCommand::Clear();
	

	Independent::Renderer2D::BeginScene(m_Camera);
	m_Level.OnRender();
	Independent::Renderer2D::EndScene();
}

void GameLayer::OnImGuiRender()
{
	//ImGui::Begin("Settings");
	//m_Level.OnImGuiRender();
	//ImGui::End();

	//Some UI

	switch (m_State)
	{
		case GameState::Play:
		{
			uint32_t playerScore = m_Level.GetPlayer().GetScore();
			Independent::String scoreStr = Independent::String("Score: ") + std::to_string(playerScore);
			ImGui::GetForegroundDrawList()->AddText(m_Font, 48.0f, ImGui::GetWindowPos(), 0xffffffff, scoreStr.c_str());
			break;
		}
		case GameState::MainMenu:
		{
			auto pos = ImGui::GetWindowPos();
			auto width = Independent::Application::Get().GetWindow().GetWidth();
			auto height = Independent::Application::Get().GetWindow().GetHeight();
			pos.x += width * 0.5f - 300.f;
			pos.y += 50.0f;
			if(m_Blink)
				ImGui::GetForegroundDrawList()->AddText(m_Font, 120.0f, pos, 0xffffffff, "Click to Play!");
			break;
		}
		case GameState::GameOver:
		{
			auto pos = ImGui::GetWindowPos();
			auto width = Independent::Application::Get().GetWindow().GetWidth();
			auto height = Independent::Application::Get().GetWindow().GetHeight();
			pos.x += width * 0.5f - 300.f;
			pos.y += 50.0f;
			if (m_Blink)
				ImGui::GetForegroundDrawList()->AddText(m_Font, 120.0f, pos, 0xffffffff, "Click to Play!");

			pos.x += 100.0f;
			pos.y += 100.0f;
			uint32_t playerScore = m_Level.GetPlayer().GetScore();
			Independent::String scoreStr = Independent::String("Score: ") + std::to_string(playerScore);
			ImGui::GetForegroundDrawList()->AddText(m_Font, 48.0f, pos, 0xffffffff, scoreStr.c_str());
			break;
		}
	}

}

void GameLayer::OnEvent(Independent::Event& e)
{
	Independent::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<Independent::WindowResizeEvent>(IDPD_BIND_EVENT_FN(GameLayer::OnWindowResize));
	dispatcher.Dispatch<Independent::MouseButtonPressedEvent>(IDPD_BIND_EVENT_FN(GameLayer::OnMouseButtonPressed));
}

bool GameLayer::OnMouseButtonPressed(Independent::MouseButtonPressedEvent& e)
{
	if (m_State == GameState::GameOver)
		m_Level.Reset();
	m_State = GameState::Play;
	return false; 
}

bool GameLayer::OnWindowResize(Independent::WindowResizeEvent& e)
{
	CreateCamera(e.GetWidth(), e.GetHeight());
	return false;
}

void GameLayer::CreateCamera(uint32_t width, uint32_t height)
{
	float aspectRatio = (float)width / (float)height;

	float cameraWidth = 8.0f;
	float bottom = -cameraWidth;
	float top = cameraWidth;
	float left = bottom * aspectRatio;
	float right = top * aspectRatio;
	m_Camera = std::make_shared<Independent::OrthographicCamera>(left, right, bottom, top);
}
