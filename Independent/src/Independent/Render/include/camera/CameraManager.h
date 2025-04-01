#pragma once

#include "Independent/Core/include/containers/SharedPtr.h"
#include "Independent/Core/include/containers/UnorderedMap.h"
#include "Independent/Core/include/containers/String.h"

#include "CameraBase.h"

namespace Independent {

	class CameraManager
	{
	public:
		static void AddCamera(const String& name, SharedPtr<CameraBase> camera);
		static void RemoveCamera(const String& name);

		static void SetActiveCamera(const String& name);
		static SharedPtr<CameraBase> GetActiveCamera();

		static bool HasCamera(const String& name);

	private:
		static UnorderedMap<String, SharedPtr<CameraBase>> s_Cameras;
		static SharedPtr<CameraBase> s_ActiveCamera;
	};

}