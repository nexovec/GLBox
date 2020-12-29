# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 2.8.11)
project (HELLO)
# set(GLFW_BUILD_EXAMPLES TRUE) {% endcomment %}
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glad)

add_subdirectory (src)
find_package(OpenGL REQUIRED)