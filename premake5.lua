workspace "Independent"
	architecture "x64"
	startproject "TestingProject"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution dir)
IncludeDir = {}
IncludeDir["GLFW"] = "Independent/vendor/GLFW/include"
IncludeDir["Glad"] = "Independent/vendor/Glad/include"
IncludeDir["ImGui"] = "Independent/vendor/imgui"
IncludeDir["glm"] = "Independent/vendor/glm"
IncludeDir["stb_image"] = "Independent/vendor/stb_image"

group "Dependencies"
	include "Independent/vendor/GLFW"
	include "Independent/vendor/Glad"
	include "Independent/vendor/imgui"
group ""


project "Independent"
	location "Independent"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	buildoptions "/utf-8"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-intermediate/" .. outputdir .. "/%{prj.name}")

	pchheader "idpdpch.h"
	pchsource "Independent/src/idpdpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	defines 
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"
		

		defines
		{
			"IDPD_PLATFORM_WINDOWS",
			"IDPD_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "IDPD_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "IDPD_Release"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "IDPD_DIST"
		runtime "Release"
		optimize "on"

project "TestingProject"
	location "TestingProject"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	buildoptions "/utf-8"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-intermediate/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Independent/vendor/spdlog/include",
		"Independent/src",
		"Independent/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Independent"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"IDPD_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "IDPD_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "IDPD_Release"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "IDPD_DIST"
		runtime "Release"
		optimize "on"