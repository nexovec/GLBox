-- premake5.lua
workspace 'GLBox'
startproject "Sandbox"
configurations {'Debug', 'Release'}
platforms {'Win32', 'Win64', 'Xbox360'}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
group 'Dependencies'
include './vendor/glfw'
include './vendor/glad'
group ''
project 'Sandbox'
kind 'ConsoleApp'
language 'C++'
cppdialect 'C++20'
targetdir 'bin/%{cfg.buildcfg}'
includedirs {'./src', "vendor/glm", './vendor/glad/include', './vendor/glfw/include'}
links {
    'GLFW',
    'Glad'
}
defines {'GLFW_INCLUDE_NONE'}

files {
    'src/**.hpp',
    'src/**.cpp',
    "vendor/glm/glm/**.hpp",
    "vendor/glm/glm/**.inl"
}

filter 'configurations:Debug'
defines {'DEBUG'}
symbols 'On'

filter 'configurations:Release'
defines {'NDEBUG'}
optimize 'On'
