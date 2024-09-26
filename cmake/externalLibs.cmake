set(IMGUI_PATH  "${EXTERN_LIBS_PATH}/ImGUI")
file(GLOB IMGUI_SOURCES ${IMGUI_PATH}/*.cpp) 
add_library("ImGui" STATIC ${IMGUI_SOURCES} 
                           ${IMGUI_PATH}/backends/imgui_impl_opengl3.cpp
                           ${IMGUI_PATH}/backends/imgui_impl_glfw.cpp)
target_include_directories("ImGui" PUBLIC ${IMGUI_PATH})


add_library("stb_image" STATIC     
    ${EXTERN_LIBS_PATH}/stb/stb_image.h
    ${EXTERN_LIBS_PATH}/stb/stb_image.c
)
target_include_directories("stb_image" 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/external/stb
)


set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(${EXTERN_LIBS_PATH}/GLFW "${CMAKE_BINARY_DIR}/glfw")
include_directories(${EXTERN_LIBS_PATH}/GLFW/include)

add_subdirectory(${EXTERN_LIBS_PATH}/GLEW "${CMAKE_BINARY_DIR}/glew")
include_directories(${EXTERN_LIBS_PATH}/GLEW/include)

add_subdirectory(${EXTERN_LIBS_PATH}/GLM "${CMAKE_BINARY_DIR}/glm")
include_directories(${EXTERN_LIBS_PATH}/GLM/glm)
