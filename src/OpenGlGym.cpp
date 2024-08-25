#include "OpenGlGym.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <array>
#include <cassert>

#define DebugGlCall(x) while (glGetError());\
    x;\
    assert(GlLogCall());

OpenGlGym::~OpenGlGym()
{
    glfwTerminate();
}

bool OpenGlGym::GlLogCall()
{
	while (auto error = glGetError()) 
	{
		std::cout << "[OpenGL error]" << error << std::endl;
        return false;
	}
    return true;
}

bool OpenGlGym::Init()
{
    /* Initialize the library */
    if (glfwInit() == GLFW_FALSE)
        return false;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
    if (!window)
    {
        return false;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (auto glewInitStat = glewInit(); glewInitStat != GLEW_OK)
    {
        std::cerr << "GLEW init failed (" << glewInitStat << ")" << std::endl;
        return false;
    }
    m_initilized = true;

    return m_initilized;
}

OpenGlGym::ShaderProgramSource OpenGlGym::ParseShader(const std::string& path)
{
    enum class ShaderType
    {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };
    ShaderType type = ShaderType::NONE;

    std::ifstream stream(path);
    std::string line;
    std::stringstream ss[2];

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

unsigned int OpenGlGym::CompileShader(unsigned int type, const std::string_view source)
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

unsigned int OpenGlGym::CreateShader(const std::string& path)
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

void OpenGlGym::CreateVertexBuffer()
{
    unsigned int v_buff;
    glGenBuffers(1, &v_buff);
    glBindBuffer(GL_ARRAY_BUFFER, v_buff);

    std::array vertices { -0.5F, -0.5F,   // 0
                           0.5F, -0.5F,   // 1
                           0.5F,  0.5F,   // 2
                          -0.5F,  0.5F }; // 3

    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(vertices)), vertices.data(),
                 GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, nullptr);
}

void OpenGlGym::CreateIndexBuffer()
{
    unsigned int ibo {};
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    std::array indices { 0u, 1u, 2u,
                         2u, 3u, 0u };
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 static_cast<GLsizeiptr>(sizeof(indices)),
                 indices.data(),
                 GL_STATIC_DRAW);
}

void OpenGlGym::CreateShaderProgram()
{
#ifdef RES_FOLDER
    std::string resFolder = RES_FOLDER;
#else
    std::string resFolder {};
#endif
    glUseProgram(CreateShader(resFolder + "/shaders/Basic.shader"));
}

void OpenGlGym::CreateDrawElement() const
{
    if (!m_initilized)
        return;

    CreateVertexBuffer();
    CreateIndexBuffer();
    CreateShaderProgram();
}

void OpenGlGym::RenderLoop() const
{
    if (!m_initilized)
        return;

    /* Loop until the user closes the window */
    while (glfwWindowShouldClose(window) == GLFW_FALSE)
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        DebugGlCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
}
