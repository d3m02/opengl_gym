#pragma once 

#include <string_view>
#include <string>
#include <unordered_map>

#include <GL/glew.h>
#include <glm.hpp>

#include "OGGCommon.hpp"

class Shader 
{
public:
    explicit Shader(const std::string& path);
    ~Shader();

    void Bind() const;
    void Unbind() const;
    
    template<std::size_t N>
    void SetUniform4f(const std::string& name, const float(&values)[N])
    {
        static_assert(N == 4, "The function requires exactly 4 float values.");
        GlCall(glUniform4f(GetUniformLocation(name), values[0], values[1], values[2], values[3]));
    }

    
    template<std::size_t N>
    void SetUniform1iv(const std::string& name, const int(&values)[N])
    {
        GlCall(glUniform1iv(GetUniformLocation(name), N, &values[0]));
    }

    
    void SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
    {
        GlCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
    }

    void SetUniform1i(const std::string& name, int val)
    {
        GlCall(glUniform1i(GetUniformLocation(name), val));
    }


private:
    struct ShaderProgramSource
    {
        std::string VertexSource;
        std::string FragmentSource;
    };

    static Shader::ShaderProgramSource ParseShader(std::string_view path);
    static unsigned int CompileShader(unsigned int type, std::string_view source);
    static unsigned int CreateShader(std::string_view path);

    int GetUniformLocation(const std::string& name);  

    unsigned int m_rendererID {0};
    std::string m_path;
    std::unordered_map<std::string, int> m_uLocationCache;
    mutable bool m_isBound { false };
};