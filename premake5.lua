workspace "ForLatte"
	architecture "x64"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include direction relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "ForLatte/vender/GLFW/include"

include "ForLatte/vender/GLFW"

project "ForLatte"
	location "ForLatte"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "flpch.h"
	pchsource "ForLatte/src/flpch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"ForLatte/vender/spdlog/include",
		"ForLatte/src",
		"%{IncludeDir.GLFW}"
	}

	links {
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "c++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"FL_PLATFORM_WINDOWS",
			"FL_BUILD_DLL"
		}

		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox/")
		}

	filter "configurations:Debug"
		defines "FL_DEBUG"
		symbols "On"
	
	filter "configurations:Release"
		defines "FL_RELEASE"
		symbols "On"

	filter "configurations:Dist"
		defines "FL_DIST"
		symbols "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"ForLatte/vender/spdlog/include",
		"ForLatte/src"
	}

	links {
		"ForLatte"
	}

	filter "system:windows"
		cppdialect "c++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"FL_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "FL_DEBUG"
		symbols "On"
	
	filter "configurations:Release"
		defines "FL_RELEASE"
		symbols "On"

	filter "configurations:Dist"
		defines "FL_DIST"
		symbols "On"
