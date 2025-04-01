#pragma once

#include "CameraBase.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Independent {

	class OrthographicCamera : public CameraBase
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top, float nearClip = -1.0f, float farClip = 1.0f);

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position);

		float GetRotation() const { return m_Rotation; }
		void SetRotation(float rotation); // Only Z-axis cause 2D-camera

		const glm::mat4& GetViewMatrix() const override { return m_ViewMatrix; }
		const glm::mat4& GetProjectionMatrix() const override { return m_ProjectionMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const override { return m_ViewProjectionMatrix; }

	private:
		void UpdateViewMatrix();
		void UpdateProjectionMatex();
		void UpdateViewProjectionMatrix();

	private:
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		float m_Rotation = 0.0f;
	};

}