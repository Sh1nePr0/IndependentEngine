#include "idpdpch.h"
#include "Independent/Render/include/camera/OrthographicCamera.h"


namespace Independent {


	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float nearClip /*= -1.0f*/, float farClip /*= 1.0f*/)
	{
		IDPD_PROFILE_FUNCTION();

		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, nearClip, farClip);
		UpdateViewMatrix();
	}

	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
	{
		IDPD_PROFILE_FUNCTION();

		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		UpdateViewMatrix();
	}

	void OrthographicCamera::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
		UpdateViewMatrix();
	}

	void OrthographicCamera::SetRotation(float rotation)
	{
		m_Rotation = rotation;
		UpdateViewMatrix();
	}

	void OrthographicCamera::UpdateViewMatrix()
	{
		IDPD_PROFILE_FUNCTION();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * 
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0.0f, 0.0f, 1.0f));

		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::UpdateProjectionMatex()
	{

	}

	void OrthographicCamera::UpdateViewProjectionMatrix()
	{

	}

}