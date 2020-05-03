workspace "HazelRoids"
    architecture "x86_64"
    startproject "HazelRoids"
    
    configurations {
        "Debug",
        "Release",
        "Dist"
    }
    
    flags
    {
        "MultiProcessorCompile",
    }

    outputdir = "%{cfg.buildcfg}_%{cfg.system}_%{cfg.architecture}"

    IncludeDir = {}
    IncludeDir["engine"] = "D:/Hazel"
    
    IncludeDir["vendor"] = "%{IncludeDir.engine}/Hazel/vendor"
    IncludeDir["glm"] = "%{IncludeDir.vendor}/glm"
    IncludeDir["log"] = "%{IncludeDir.vendor}/spdlog/include"
    IncludeDir["misc"] = "vendor"

group "Dependencies"
    
group""
    project "HazelRoids"
        location "HazelRoids"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++17"
        staticruntime "On"

        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
        objdir ("bin/int/" .. outputdir .. "/%{prj.name}")
        
        --pchheader "exgpch.h"
        --pchsource "HazelRoids/src/exgpch.cpp"

        defines {
        }
        
        files {
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp",
        }

        includedirs {
            "%{IncludeDir.engine}/Hazel/src",
            "%{IncludeDir.glm}",
            "%{IncludeDir.log}",
            "%{prj.name}/src",
        }

        links {
            "Hazel.lib",
            "GLFW.lib",
            "Glad.lib",
            "ImGui.lib",
        }

        filter "system:windows"
            systemversion "latest"
        
        filter "configurations:Debug"
            defines "HZ_DEBUG"
            runtime "Debug"
            symbols "On"
        
            libdirs {
                "%{IncludeDir.engine}/bin/Debug-windows-x86_64/Hazel",
                "%{IncludeDir.vendor}/glfw/bin/Debug-windows-x86_64/GLFW",
                "%{IncludeDir.vendor}/glad/bin/Debug-windows-x86_64/Glad",
                "%{IncludeDir.vendor}/imgui/bin/Debug-windows-x86_64/ImGui",
            }
        
        filter "configurations:Release"
            defines "HZ_RELEASE"
            runtime "Release"
            optimize "On"
        
            libdirs {
                "%{IncludeDir.engine}/bin/Release-windows-x86_64/Hazel/",
                "%{IncludeDir.vendor}/glfw/bin/Release-windows-x86_64/GLFW",
                "%{IncludeDir.vendor}/glad/bin/Release-windows-x86_64/Glad",
                "%{IncludeDir.vendor}/imgui/bin/Release-windows-x86_64/ImGui",
            }
            
        filter "configurations:Dist"
            defines "HZ_DIST"
            runtime "Release"
            optimize "On"
            
            libdirs {
                "%{IncludeDir.engine}/bin/Dist-windows-x86_64/Hazel/",
                "%{IncludeDir.vendor}/glfw/bin/Dist-windows-x86_64/GLFW",
                "%{IncludeDir.vendor}/glad/bin/Dist-windows-x86_64/Glad",
                "%{IncludeDir.vendor}/imgui/bin/Dist-windows-x86_64/ImGui",
            }
        
        
                    