#include "OpenGlGym.hpp"

#include <iostream>

#include <array>

#include "Common.hpp"
#include "Renderer.hpp"
#include "VertexBuffer.hpp"
#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "Shader.hpp"

OpenGlGym::~OpenGlGym()
{
    glfwTerminate();
}

bool OpenGlGym::Init()
{
    /* Initialize the library */
    if (glfwInit() == GLFW_FALSE || m_initilized)
        return false;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    pWindow = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
    if (!pWindow)
    {
        return false;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(pWindow);

    if (auto glewInitStat = glewInit(); glewInitStat != GLEW_OK)
    {
        std::cerr << "GLEW init failed (" << glewInitStat << ")" << std::endl;
        return false;
    }
    m_initilized = true;

    return m_initilized;
}

void OpenGlGym::Run()
{
    if (!m_initilized)
        return;
    
    std::array vertices { -0.5F, -0.5F,   // 0
                           0.5F, -0.5F,   // 1
                           0.5F,  0.5F,   // 2
                          -0.5F,  0.5F }; // 3
    std::array indices { 0U, 1U, 2U,
                         2U, 3U, 0U };
                         
#ifdef RES_FOLDER
    std::string resFolder = RES_FOLDER;
#else
    std::string resFolder {};
#endif

    VertexArray va;
    VertexBuffer vb(vertices.data(), sizeof(vertices));

    VertexBufferLayout layout;
    layout.Push<float>(2);
    
    va.AddBuffer(vb, layout);

    /* Index buffer */

    IndexBuffer ib(indices.data(), sizeof(indices));

    Shader shader(resFolder + "/shaders/Basic.shader");
    Renderer renderer;
    float r {0.5F};
    float increment {0.05F};

    /* Loop until the user closes the window */
    while (glfwWindowShouldClose(pWindow) == GLFW_FALSE)
    {
        renderer.Clear();
        /* Draw flow */

        shader.Bind();
        shader.SetUniform4f("u_Color", {r, 0.5F, 0.5F, 1.0F});
        renderer.Draw(va, ib, shader);
        
        /* Post processing */
        if (r > 1.0F)
            increment = -0.05F;
        else if (r < 0.0F)
            increment = 0.05F;
        r += increment;

        /* Swap front and back buffers */
        glfwSwapBuffers(pWindow);

        /* Poll for and process events */
        glfwPollEvents();
    }
}
