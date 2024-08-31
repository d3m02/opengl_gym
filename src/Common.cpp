#include "Common.hpp"

#include <iostream>

bool GlLogCall()
{
    while (auto error = glGetError())
    {
        std::cout << "[OpenGL error]" << error << "\n";
        return false;
    }
    return true;
}