cmake_minimum_required(VERSION 3.27)
project(OpenGlGym)

include(cmake/config.cmake)
include(cmake/externalLibs.cmake)

add_subdirectory(src/Common)
add_subdirectory(src/OpenGlAbstraction)
add_subdirectory(src/Playtests)

add_executable(OpenGlGym src/main.cpp)

target_sources(OpenGlGym
    PRIVATE             
        src/OpenGlGym.hpp
        src/OpenGlGym.cpp
)

target_link_libraries(OpenGlGym
    PUBLIC 
        ImGui
    PRIVATE
        OGG::OpenGlAbstraction
        OGG::Playtests
        OGG::Common
)