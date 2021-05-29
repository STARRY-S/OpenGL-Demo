cmake_minimum_required(VERSION 3.0)

project(
    "learn OpenGL"
    LANGUAGES C
    VERSION 0.1.0
)

set(C_FLAGS "-Wall -g -lm -ldl -std=c11")
set(CMAKE_C_FLAGS ${C_FLAGS})
set(OpenGL_GL_PREFERENCE LEGACY)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

configure_file(src/glsl/cube.v.glsl cube.v.glsl COPYONLY)
configure_file(src/glsl/cube.f.glsl cube.f.glsl COPYONLY)
configure_file(src/glsl/floor.v.glsl floor.v.glsl COPYONLY)
configure_file(src/glsl/floor.f.glsl floor.f.glsl COPYONLY)

include_directories(${OPENGL_INCLUDE_DIR} src)

aux_source_directory("src" GLSRC)
add_executable(main ${GLSRC})
target_link_libraries(main ${OPENGL_gl_LIBRARY} glfw)
