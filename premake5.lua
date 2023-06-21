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

        pchheader "pch.h"
        pchsource "src/pch.cpp"

        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
        objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

        files {
            "%{prj.name}/src/**.*",
            "%{prj.name}/libraries/**.*"
        }

        includedirs {
            "%{prj.name}/libraries/include",
            "%{prj.name}/src"
        }

        libdirs {
            "%{prj.name}/libraries/lib"
        }

        links {
            "glfw3.lib",
            "opengl32.lib"
        }

        filter "system:windows"
            systemversion "latest"

            defines {
                "PHSX2D_BUILD_DLL",
                "PHSX2D_PLATFORM_WINDOWS",
            }

        filter "files:glad.c or files:stb_image.cpp"
            flags { "NoPCH" }

        filter "files:pch.cpp"
            buildoptions { "/Yc\"pch.h\"" }

        filter "configurations:Debug"
            defines "PHSX2D_DEBUG"
            symbols "on"

        filter "configurations:Release"
            defines "PHSX2D_RELEASE"
            optimize "on"

        filter "configurations:Dist"
            defines "PHSX2D_DIST"
            optimize "on"

    project "SandBox"
        location "SandBox"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++20"
        staticruntime "on"

        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
        objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

        files {
            "%{prj.name}/src/**.*"
        }

        includedirs {
            "Physx2D/libraries/include",
            "Physx2D/src"
        }

        links {
            "Physx2D"
        }

        filter "system:windows"
            systemversion "latest"

            defines {
                "PHSX2D_PLATFORM_WINDOWS"
            }

        filter "configurations:Debug"
            defines "PHSX2D_DEBUG"
            symbols "on"

        filter "configurations:Release"
            defines "PHSX2D_RELEASE"
            optimize "on"

        filter "configurations:Dist"
            defines "PHSX2D_DIST"
            optimize "on"
