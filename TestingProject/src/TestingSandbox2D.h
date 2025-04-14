#pragma once

#include <Independent.h>


class TestingSandbox2D : public Independent::Layer
{
public:
	TestingSandbox2D();
	virtual ~TestingSandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Independent::Timestep ts) override;
	virtual void OnImGuiRenderer() override;
	void OnEvent(Independent::Event& e) override;

private:
	Independent::OrthographicCameraController m_CameraController;

	Independent::SharedPtr<Independent::Texture2D> m_SpruceTreeTexture;
	Independent::SharedPtr<Independent::Texture2D> m_WitcherLogoTexture;
	Independent::SharedPtr<Independent::Texture2D> m_CheckerboardTexture;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f};
};