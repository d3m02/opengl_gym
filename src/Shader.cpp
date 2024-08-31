#include "Shader.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <sstream>
#include <fstream>
#include <iostream>
#include <cassert>

Shader::Shader(const std::string& path)
    : m_path(path)
{
    m_rendererID = CreateShader(path);
}

Shader::~Shader()
{
    glDeleteProgram(m_rendererID);
}

unsigned int Shader::CreateShader(std::string_view path)
{
    ShaderProgramSource source = ParseShader(path);
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, source.VertexSource);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, source.FragmentSource);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

Shader::ShaderProgramSource Shader::ParseShader(std::string_view path)
{
    enum class ShaderType
    {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };
    ShaderType type = ShaderType::NONE;

    std::ifstream stream(path.data());
    std::string line;
    std::array<std::stringstream, 2> ss;

    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else if (type != ShaderType::NONE)
        {
            ss[static_cast<int>(type)] << line << '\n';
        }
    }
    return {.VertexSource = ss[0].str(), .FragmentSource = ss[1].str()};
}

unsigned int Shader::CompileShader(unsigned int type, std::string_view source)
{
    auto id = glCreateShader(type);
    const char* src = source.data();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result {GL_FALSE};
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        auto* message = static_cast<char*>(alloca(length * sizeof(char)));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
                  << " shader: " << message << std::endl;

        glDeleteShader(id);
        return 0;
    }
    return id;
}

void Shader::Bind() const
{
    glUseProgram(m_rendererID);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}


int Shader::GetUniformLocation(const std::string& name)
{
    if (!m_uLocationCache.contains(name))
        m_uLocationCache[name] = glGetUniformLocation(m_rendererID, name.c_str());
    if (m_uLocationCache[name] == -1)
        std::cout << "uniform '" << name << "' doesn't exist in shader\n";
    return m_uLocationCache[name]; 
}