#pragma once

#include "Independent/Core/include/containers/SharedPtr.h"
#include "Independent/Core/include/containers/UnorderedMap.h"
#include "Independent/Core/include/containers/String.h"

#include "CameraBase.h"

namespace Independent {

	class CameraManager
	{
	public:
		static void AddCamera(SharedPtr<CameraBase> camera);
		static void RemoveCamera(SharedPtr<CameraBase> camera);

	private:
		static UnorderedMap<String, SharedPtr<CameraBase>> s_Cameras;
		static SharedPtr<CameraBase> s_ActiveCamera;
	};

}