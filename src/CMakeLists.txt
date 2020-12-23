link_libraries(glfw glad)
include_directories("${GLFW_SOURCE_DIR}/include")
include_directories("${HELLO_SOURCE_DIR}/vendor/glad/include")
add_executable (hello main.c ${GLAD_GL})