cmake_minimum_required(VERSION 3.27)
project(opengl)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(opengl src/main.cpp)

target_include_directories(opengl PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_sources(opengl
    PRIVATE     
        src/OpenGlGym.cpp
        include/OpenGlGym.hpp
)

add_compile_definitions (RES_FOLDER="${CMAKE_CURRENT_SOURCE_DIR}/res")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(external/GLFW)
include_directories(external/GLFW/include)
target_link_libraries(opengl PRIVATE glfw)

add_subdirectory(external/GLEW)
target_include_directories(opengl PRIVATE external/GLEW/include)
target_link_libraries(opengl PRIVATE libglew_static)