cmake_minimum_required(VERSION 3.27)
project(OpenGlGym)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(OpenGlGym src/main.cpp)

target_include_directories(OpenGlGym PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include  ${CMAKE_CURRENT_SOURCE_DIR}/tests)
target_sources(OpenGlGym
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

        tests/TestBase.hpp
        tests/TestMenu.hpp
        tests/TestMenu.cpp
        tests/TestClearColor.hpp
        tests/TestClearColor.cpp
)


target_include_directories(OpenGlGym PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/external/stb)
target_sources(OpenGlGym
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
target_link_libraries(OpenGlGym PRIVATE glfw)

add_subdirectory(external/GLEW)
target_include_directories(OpenGlGym PRIVATE external/GLEW/include)
target_link_libraries(OpenGlGym PRIVATE libglew_static)

add_subdirectory(external/GLM)
target_include_directories(OpenGlGym PRIVATE external/GLM/glm)
target_link_libraries(OpenGlGym PRIVATE glm::glm)

set(IMGUI_PATH  "external/ImGUI")
    
# Compile as static library 
file(GLOB IMGUI_SOURCES ${IMGUI_PATH}/*.cpp) 
add_library("ImGui" STATIC ${IMGUI_SOURCES} 
                           ${IMGUI_PATH}/backends/imgui_impl_opengl3.cpp
                           ${IMGUI_PATH}/backends/imgui_impl_glfw.cpp)
target_include_directories("ImGui" PUBLIC ${IMGUI_PATH})
target_link_libraries(OpenGlGym PUBLIC ImGui)