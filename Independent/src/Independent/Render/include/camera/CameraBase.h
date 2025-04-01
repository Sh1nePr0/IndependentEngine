#pragma once

#include <glm/glm.hpp>
#include "Independent/Core/include/containers/String.h"

namespace Independent {

	class CameraBase
	{
	public:
		virtual ~CameraBase() = default;
		virtual const glm::mat4& GetViewMatrix() const = 0;
		virtual const glm::mat4& GetProjectionMatrix() const = 0;
		virtual const glm::mat4& GetViewProjectionMatrix() const = 0;
	};

}