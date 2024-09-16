cmake_minimum_required(VERSION 3.27)
project(opengl)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(opengl src/main.cpp)

target_include_directories(opengl PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_sources(opengl
    PRIVATE     
        include/OpenGlGym.hpp
        include/Common.hpp
        include/VertexBuffer.hpp
        include/IndexBuffer.hpp
        include/VertexBufferLayout.hpp
        include/VertexArray.hpp
        include/Shader.hpp
        include/Renderer.hpp
        include/Texture.hpp
        
        src/OpenGlGym.cpp
        src/Common.cpp
        src/VertexBuffer.cpp
        src/IndexBuffer.cpp
        src/VertexArray.cpp
        src/Shader.cpp
        src/Renderer.cpp
        src/Texture.cpp
)


target_include_directories(opengl PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/external/stb)
target_sources(opengl
    PRIVATE     
        external/stb/stb_image.h
        external/stb/stb_image.c
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

add_subdirectory(external/GLM)
target_include_directories(opengl PRIVATE external/GLM/glm)
target_link_libraries(opengl PRIVATE glm::glm)