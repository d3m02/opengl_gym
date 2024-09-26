add_library(OpenGlAbstraction STATIC)
add_library(OGG::OpenGlAbstraction ALIAS OpenGlAbstraction)

target_sources(OpenGlAbstraction
    PUBLIC FILE_SET HEADERS
    BASE_DIRS 
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
    FILES 
        VertexBuffer.hpp
        IndexBuffer.hpp
        VertexBufferLayout.hpp
        VertexArray.hpp
        Shader.hpp
        Renderer.hpp
        Texture.hpp
    PRIVATE
        VertexBuffer.cpp
        IndexBuffer.cpp
        VertexArray.cpp
        Shader.cpp
        Renderer.cpp
        Texture.cpp
)


set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

target_link_libraries(OpenGlAbstraction 
        PUBLIC 
            glfw
            libglew_static
            glm::glm
            stb_image
        PRIVATE
            OGG::Common
)
