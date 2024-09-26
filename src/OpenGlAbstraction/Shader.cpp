#include "Shader.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cstdint>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cassert>
#include <utility>

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
    enum class ShaderType : int8_t
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
        if (line.contains("#shader"))
        {
            if (line.contains("vertex"))
                type = ShaderType::VERTEX;
            else if (line.contains("fragment"))
                type = ShaderType::FRAGMENT;
        }
        else if (type != ShaderType::NONE)
        {
            ss[std::to_underlying(type)] << line << '\n';
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
    if (m_isBound)
        return;

    glUseProgram(m_rendererID);
    m_isBound = true;
}

void Shader::Unbind() const
{
    if (!m_isBound)
        return;
    
    glUseProgram(0);
    m_isBound = false;
}


int Shader::GetUniformLocation(const std::string& name)
{
    auto it = m_uLocationCache.find("key");
    if (it == m_uLocationCache.end())
        it = m_uLocationCache.emplace(name, glGetUniformLocation(m_rendererID, name.c_str())).first;
        
    if (it->second == -1)
        std::cout << "uniform '" << name << "' doesn't exist in shader\n";
    
    return it->second; 
}