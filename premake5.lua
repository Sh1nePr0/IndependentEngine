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

project "Independent"
	location "Independent"
	kind "SharedLib"
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
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src"
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
		symbols "On"

	filter "configurations:Release"
		defines "IDPD_Release"
		optimize "On"

	filter "configurations:Dist"
		defines "IDPD_DIST"
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
		symbols "On"

	filter "configurations:Release"
		defines "IDPD_Release"
		optimize "On"

	filter "configurations:Dist"
		defines "IDPD_DIST"
		optimize "On"