#pragma once

#include <glm/glm.hpp>

namespace Independent {

	class CameraBase
	{
	public:
		virtual ~CameraBase() = default;
		virtual const glm::mat4& GetViewMatrix() const = 0;
		virtual const glm::mat4& GetProjectionMatrix() const = 0;
		virtual void RecalculateViewMatrix() = 0;
	};

}