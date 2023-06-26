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

        libdirs {
            "%{prj.name}/libraries/lib"
        }

        links {
            "glfw3.lib",
            "opengl32.lib"
        }


        filter "system:windows"
            systemversion "latest"
            
            postbuildcommands {
                "{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/SandBox",
            }

            defines {
                "PHSX2D_BUILD_DLL",
                "PHSX2D_PLATFORM_WINDOWS",
            }

        filter "configurations:Debug"
            defines {"PHSX2D_DEBUG", "PHSX2D_ASSERT_ENABLE"}
            symbols "on"

        filter "configurations:Release"
            defines {"PHSX2D_RELEASE", "PHSX2D_ASSERT_ENABLE"}
            optimize "on"

        filter "configurations:Dist"
            defines "PHSX2D_DIST"
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
