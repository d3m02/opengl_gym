add_library(Playtests STATIC)
add_library(OGG::Playtests ALIAS Playtests)

target_sources(Playtests
    PUBLIC FILE_SET HEADERS
    BASE_DIRS 
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
    FILES 
        TestBase.hpp
        TestMenu.hpp
        TestClearColor.hpp
        TestTexture2D.hpp
    PRIVATE
        TestMenu.cpp
        TestClearColor.cpp
        TestTexture2D.cpp
)

target_link_libraries(Playtests 
        PRIVATE
            OGG::Common
            OGG::OpenGlAbstraction
            ImGui
)
