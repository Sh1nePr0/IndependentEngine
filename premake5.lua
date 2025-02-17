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

include "Independent/vendor/GLFW"

project "Independent"
	location "Independent"
	kind "SharedLib"
	language "C++"
	buildoptions "/utf-8"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-intermediate/" .. outputdir .. "/%{prj.name}")

	pchheader "idpdpch.h"
	pchsource "Independent/src/idpdpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}"
	}

	links
	{
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		

		defines
		{
			"IDPD_PLATFORM_WINDOWS",
			"IDPD_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ..\\bin\\" .. outputdir .. "\\IndependentEditor")
		}

	filter "configurations:Debug"
		defines "IDPD_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "IDPD_Release"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "IDPD_DIST"
		buildoptions "/MD"
		optimize "On"

project "IndependentEditor"
	location "IndependentEditor"
	kind "ConsoleApp"
	language "C++"
	buildoptions "/utf-8"

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
		"Independent/src"
	}

	links
	{
		"Independent"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"IDPD_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "IDPD_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "IDPD_Release"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "IDPD_DIST"
		buildoptions "/MD"
		optimize "On"