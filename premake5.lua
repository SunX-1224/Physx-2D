workspace "Physx2D"
    architecture "x64"

    configurations {
        "Debug",
        "Release",
        "Dist"
    }

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    project "Physx2D"
        location "Physx2D/"
        kind "SharedLib"
        language "C++"
        cppdialect "C++20"
        staticruntime "off"

        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
        objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

        pchheader "pch.h"
        pchsource "%{prj.name}/src/pch.cpp"

        files {
            "%{prj.name}/src/**.*",
            "%{prj.name}/libraries/**.*"
        }

        includedirs {
            "%{prj.name}/libraries/include",
            "%{prj.name}/src"
        }

<<<<<<< HEAD
        libdirs {
            "%{prj.name}/libraries/lib"
        }
        
        filter "files:**.h"
			flags {"ExcludeFromBuild"}
	
        filter "system:windows"
            systemversion "latest"
            links {"glfw3", "opengl32"}
            postbuildcommands {"COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/SandBox"}
            defines { "PHSX2D_BUILD_DLL", "PHSX2D_PLATFORM_WINDOWS"}
=======
        libdirs {"%{prj.name}/libraries/lib_%{cfg.system}"}

        filter "system:windows"
            systemversion "latest"
            links {"glfw3", "opengl32"}
            postbuildcommands {"{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/SandBox"}
            defines {"PHSX2D_BUILD_DLL","PHSX2D_PLATFORM_WINDOWS"}
>>>>>>> d5f14d6 (project build fix)
        
        filter "system:linux"
            systemversion "latest"
            buildoptions { "-fvisibility=hidden"}
<<<<<<< HEAD
            linkoptions { "-shared" }
            links {"glfw3", "GL"}
            postbuildcommands {"{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/SandBox"}
            defines { "PHSX2D_BUILD_DLL", "PHSX2D_PLATFORM_LINUX"}
=======
            links {"glfw3", "GL"}
            postbuildcommands {"{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/SandBox"}
            defines {"PHSX2D_BUILD_DLL","PHSX2D_PLATFORM_LINUX"}
>>>>>>> d5f14d6 (project build fix)

        filter "configurations:Debug"
            defines {"PHSX2D_DEBUG", "PHSX2D_ASSERT_ENABLE"}
            symbols "on"

        filter "configurations:Release"
            defines {"PHSX2D_RELEASE", "PHSX2D_ASSERT_ENABLE"}
            optimize "on"

        filter "configurations:Dist"
            defines {"PHSX2D_DIST", "PHSX2D_ASSERT_ENABLE"}
            optimize "on"

        filter "files:**/libraries/src/**.*"
			flags { "NoPCH" }

    project "SandBox"
        location "SandBox"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++20"
        staticruntime "off"

        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
        objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

        files {
            "%{prj.name}/src/**.*",
            "%{prj.name}/res/**.*",
            "%{prj.name}/applications/**.*"
        }
        
        filter "files:**.h"
    	     flags {"ExcludeFromBuild"}

        includedirs {
            "Physx2D/libraries/include",
            "Physx2D/src"
        }

        links {"Physx2D"}

        filter "system:windows"
            systemversion "latest"
<<<<<<< HEAD
            postbuildcommands {"{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/SandBox"}
            defines {"PHSX2D_BUILD_DLL","PHSX2D_PLATFORM_WINDOWS"}
	
		filter "system:linux"
            systemversion "latest"
            postbuildcommands {"{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/SandBox"}
            defines {"PHSX2D_BUILD_DLL","PHSX2D_PLATFORM_LINUX"}
        
		filter "configurations:Debug"
            defines {"PHSX2D_DEBUG", "PHSX2D_ASSERT_ENABLE"}
=======
            defines "PHSX2D_PLATFORM_WINDOWS"

        filter "configurations:Debug"
            defines "PHSX2D_DEBUG"
>>>>>>> d5f14d6 (project build fix)
            symbols "on"

		filter "configurations:Release"
            defines {"PHSX2D_RELEASE", "PHSX2D_ASSERT_ENABLE"}
            optimize "on"

		filter "configurations:Dist"
            defines {"PHSX2D_DIST", "PHSX2D_ASSERT_ENABLE"}
            optimize "on"
