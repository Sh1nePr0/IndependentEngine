#include <ImGui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

#include "TestingSandbox2D.h"

TestingSandbox2D::TestingSandbox2D()
	: Layer("TestingSandbox2D"), m_CameraController(1280.0f / 720.f, true)
{

}

void TestingSandbox2D::OnAttach()
{
	m_SpruceTreeTexture = Independent::Texture2D::Create("assets/textures/spruceTree.png");
	m_WitcherLogoTexture = Independent::Texture2D::Create("assets/textures/witcherLogo.png");
	m_CheckerboardTexture = Independent::Texture2D::Create("assets/textures/checkerboardTexture.png");
}

void TestingSandbox2D::OnDetach()
{

}

void TestingSandbox2D::OnUpdate(Independent::Timestep ts)
{
	//Update
	m_CameraController.OnUpdate(ts);

	//Render
	Independent::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Independent::RenderCommand::Clear();

	Independent::Renderer2D::BeginScene(std::make_shared<Independent::OrthographicCamera>(m_CameraController.GetCamera()));
	Independent::Renderer2D::DrawQuad({-1.0f, 0.0f}, {0.8f, 0.8f}, {0.2f, 0.2f, 0.8f, 1.0f});
	Independent::Renderer2D::DrawQuad({0.5f, -0.5f}, {0.5f, 0.75f}, {0.8f, 0.2f, 0.3f, 1.0f});
	Independent::Renderer2D::DrawQuad({0.0f, 0.0f, -0.1f}, { 10.0f, 10.0f }, m_CheckerboardTexture);
	Independent::Renderer2D::EndScene();
}

void TestingSandbox2D::OnImGuiRenderer()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void TestingSandbox2D::OnEvent(Independent::Event& e)
{
	m_CameraController.OnEvent(e);
}
