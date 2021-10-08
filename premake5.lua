-- premake5.lua
workspace 'Test'
configurations {'Debug', 'Release'}
platforms {'Win32', 'Win64', 'Xbox360'}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
group 'Dependencies'
include './vendor/glfw'
include './vendor/glad'
group ''
project 'HelloWorld'
kind 'ConsoleApp'
language 'C'
cdialect 'C11'
targetdir 'bin/%{cfg.buildcfg}'
includedirs {'./src', './vendor/glad/include', './vendor/glfw/include'}
links {
    'GLFW',
    'Glad'
}
defines {'GLFW_INCLUDE_NONE'}

files {'src/**.h', 'src/**.c'}

filter 'configurations:Debug'
defines {'DEBUG'}
symbols 'On'

filter 'configurations:Release'
defines {'NDEBUG'}
optimize 'On'
