workspace "Independent"
	architecture "x64"
	startproject "IndependentEditor"

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

group "Dependencies"
	include "Independent/vendor/GLFW"
	include "Independent/vendor/Glad"
	include "Independent/vendor/imgui"
group ""


project "Independent"
	location "Independent"
	kind "SharedLib"
	language "C++"
	buildoptions "/utf-8"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-intermediate/" .. outputdir .. "/%{prj.name}")

	pchheader "idpdpch.h"
	pchsource "Independent/src/idpdpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
		

		defines
		{
			"IDPD_PLATFORM_WINDOWS",
			"IDPD_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/IndependentEditor/\"")
		}

	filter "configurations:Debug"
		defines "IDPD_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "IDPD_Release"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "IDPD_DIST"
		runtime "Release"
		optimize "On"

project "IndependentEditor"
	location "IndependentEditor"
	kind "ConsoleApp"
	language "C++"
	buildoptions "/utf-8"
	staticruntime "off"

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
		"Independent",
		"ImGui"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"IDPD_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "IDPD_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "IDPD_Release"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "IDPD_DIST"
		runtime "Release"
		optimize "On"