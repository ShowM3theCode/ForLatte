workspace "ForLatte"
	architecture "x64"
	startproject "Sandbox"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include direction relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "ForLatte/vender/GLFW/include"
IncludeDir["Glad"] = "ForLatte/vender/Glad/include"
IncludeDir["ImGui"] = "ForLatte/vender/imgui"
IncludeDir["glm"] = "ForLatte/vender/glm"
IncludeDir["stb_image"] = "ForLatte/vender/stb_image"

include "ForLatte/vender/GLFW"
include "ForLatte/vender/Glad"
include "ForLatte/vender/imgui"

project "ForLatte"
	location "ForLatte"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "flpch.h"
	pchsource "ForLatte/src/flpch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"{prj.name}/vender/stb_image/**.h",
		"{prj.name}/vender/stb_image/**.cpp",
		"{prj.name}/vender/glm/glm/**.hpp",
		"{prj.name}/vender/glm/glm/**.inl"
	}

	includedirs {
		"ForLatte/vender/spdlog/include",
		"ForLatte/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	links {
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines {
			"FL_PLATFORM_WINDOWS",
			"FL_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "FL_DEBUG"
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		defines "FL_RELEASE"
		runtime "Release"
		symbols "on"

	filter "configurations:Dist"
		defines "FL_DIST"
		runtime "Release"
		symbols "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "c++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"ForLatte/vender/spdlog/include",
		"ForLatte/src",
		"%{IncludeDir.glm}"
	}

	links {
		"ForLatte"
	}

	filter "system:windows"
		systemversion "latest"

		defines {
			"FL_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "FL_DEBUG"
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		defines "FL_RELEASE"
		runtime "Release"
		symbols "on"

	filter "configurations:Dist"
		defines "FL_DIST"
		runtime "Release"
		symbols "on"
