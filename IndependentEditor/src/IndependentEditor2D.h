#pragma once

#include <Independent.h>


class IndependentEditor2D : public Independent::Layer
{
public:
	IndependentEditor2D();
	virtual ~IndependentEditor2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Independent::Timestep ts) override;
	virtual void OnImGuiRenderer() override;
	void OnEvent(Independent::Event& e) override;

private:
	Independent::OrthographicCameraController m_CameraController;

	// Temp
	Independent::SharedPtr<Independent::VertexArray> m_SquareVAO;
	Independent::SharedPtr<Independent::Shader> m_FlatColorShader;
	
	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f};
};