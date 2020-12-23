link_libraries(glfw)
add_executable (hello main.c)
include_directories("${GLFW_SOURCE_DIR}/include")