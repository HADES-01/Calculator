VULKAN_SDK = os.getenv("VULKAN_SDK")
BOOST_SDK = os.getenv("BOOST_INCLUDE")

IncludeDir = {}
IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/"
IncludeDir["glm"] = "ext/glm"
IncludeDir["BOOST"] = "%{BOOST_SDK}"

workspace "Calculator"
    configurations {"Debug", "Release"}
    project "Calculator"
        kind "WindowedApp"
        language "C++"
        cppdialect "C++17"
        targetdir "bin/"
        objdir "bin-int/%{prj.name}"
        staticruntime "off"

        files {"src/**.cpp", "src/**.h"}

        includedirs {
            "src/",
            "ext/imgui/",
            "ext/glfw/include",
            "%{IncludeDir.VulkanSDK}/Include",
            "%{IncludeDir.glm}",
        }

        links {
            "GLFW",
            "ImGui",
            "dwmapi",
            "gdi32",
            "%{IncludeDir.VulkanSDK}/Lib/vulkan-1",
        }

include "ext/imgui.lua"
include "ext/glfw.lua"