#include <ImGui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

#include "IndependentEditor2D.h"

IndependentEditor2D::IndependentEditor2D()
	: Layer("IndependentEditor2D"), m_CameraController(1280.0f / 720.f, true)
{

}

void IndependentEditor2D::OnAttach()
{
	
}

void IndependentEditor2D::OnDetach()
{

}

void IndependentEditor2D::OnUpdate(Independent::Timestep ts)
{
	//Update
	m_CameraController.OnUpdate(ts);

	//Render
	Independent::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Independent::RenderCommand::Clear();

	//glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

	Independent::Renderer2D::BeginScene(std::make_shared<Independent::OrthographicCamera>(m_CameraController.GetCamera()));
	Independent::Renderer2D::DrawQuad({0.0f, 0.0f}, {1.0f, 1.0f}, {0.8f, 0.2f, 0.3, 1.0f});
	Independent::Renderer2D::EndScene();

	//for (int y = 0; y < 20; y++)
	//{
	//	for (int x = 0; x < 20; x++)
	//	{
	//		glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
	//		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
	//
	//		Independent::Renderer::Submit(m_FlatColorShader, m_SquareVAO, transform);
	//	}
	//}

	// TODO: Add these functions: Shader::SetMat4(), Shader::SetFloat4()
	//std::dynamic_pointer_cast<Independent::OpenGLShader>(m_FlatColorShader)->Bind();
	//std::dynamic_pointer_cast<Independent::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);
}

void IndependentEditor2D::OnImGuiRenderer()
{
	ImGui::Begin("Settings");

	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

	ImGui::End();
}

void IndependentEditor2D::OnEvent(Independent::Event& e)
{
	m_CameraController.OnEvent(e);
}
