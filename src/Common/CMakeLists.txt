add_library(Common STATIC)
add_library(OGG::Common ALIAS Common)

target_sources(Common
    PUBLIC FILE_SET HEADERS
    BASE_DIRS 
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
    FILES 
        OGGCommon.hpp
    PRIVATE
        Common.cpp
)

target_link_libraries(Common 
    PUBLIC 
        glfw
        libglew_static
)
