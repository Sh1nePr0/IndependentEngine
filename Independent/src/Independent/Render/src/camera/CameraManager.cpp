#include "idpdpch.h"
#include "Independent/Render/include/camera/CameraManager.h"

namespace Independent {

	UnorderedMap<String, SharedPtr<CameraBase>> CameraManager::s_Cameras;
	SharedPtr<CameraBase> CameraManager::s_ActiveCamera;

	void CameraManager::AddCamera(const String& name, SharedPtr<CameraBase> camera)
	{
		s_Cameras[name] = camera;

		if (!s_ActiveCamera)
			s_ActiveCamera = camera;
	}

	void CameraManager::RemoveCamera(const String& name)
	{
		if (s_Cameras.count(name))
		{
			if (s_Cameras[name] == s_ActiveCamera)
			{
				s_ActiveCamera = nullptr;
			}

			s_Cameras.erase(name);
		}
	}

	void CameraManager::SetActiveCamera(const String& name)
	{
		if (s_Cameras.count(name))
			s_ActiveCamera = s_Cameras[name];
	}

	SharedPtr<CameraBase> CameraManager::GetActiveCamera()
	{
		return s_ActiveCamera;
	}

	bool CameraManager::HasCamera(const String& name)
	{
		return s_Cameras.count(name) > 0;
	}


}