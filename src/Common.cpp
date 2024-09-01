#include "Common.hpp"

#include <iostream>

bool GlLogCall()
{
    while (auto error = glGetError())
    {
        switch (error)
        {
            case GL_INVALID_ENUM:       std::cout << "[OpenGL error] GL_INVALID_ENUM\n";  break;
            case GL_INVALID_VALUE:      std::cout << "[OpenGL error] GL_INVALID_VALUE\n"; break;
            case GL_INVALID_OPERATION:  std::cout << "[OpenGL error] GL_INVALID_OPERATION\n"; break;
            default:                    std::cout << "[OpenGL error]" << error << "\n"; break;
        }

        return false;
    }
    return true;
}

void GlClearErrors()
{
    while (glGetError());
}

    