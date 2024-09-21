#include "OpenGlGym.hpp"

#include <iostream>
#include <array>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <ext/matrix_clip_space.hpp>
#include <ext/matrix_transform.hpp>
#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>


#include "Common.hpp"
#include "Renderer.hpp"
#include "VertexBuffer.hpp"
#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "Shader.hpp"
#include "Texture.hpp"


OpenGlGym::~OpenGlGym()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
}

void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                                const GLchar* message, const void* userParam)
{
    fprintf(stdout, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
            (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), type, severity, message);
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
    pWindow = glfwCreateWindow(960, 540, "OpenGL gym", nullptr, nullptr);
    if (!pWindow)
    {
        return false;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(pWindow);

    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(pWindow, true);
    ImGui_ImplOpenGL3_Init();
    ImGui::StyleColorsDark();

    if (auto glewInitStat = glewInit(); glewInitStat != GLEW_OK)
    {
        std::cerr << "GLEW init failed (" << glewInitStat << ")" << std::endl;
        return false;
    }
    m_initilized = true;

    return m_initilized;

    // During init, enable debug output
    glEnable              ( GL_DEBUG_OUTPUT );
    glDebugMessageCallback( MessageCallback, 0 );
}

void OpenGlGym::Run()
{
    if (!m_initilized)
        return;
    
    std::array vertices { 100.F, 100.F, 0.0F, 0.0F,   // 0
                          400.F, 100.F, 1.0F, 0.0F,   // 1
                          400.F, 400.F, 1.0F, 1.0F,   // 2
                          100.F, 400.F, 0.0F, 1.0F }; // 3
    
    
    std::array indices { 0U, 1U, 2U,
                         2U, 3U, 0U };
                         
#ifdef RES_FOLDER
    std::string resFolder = RES_FOLDER;
#else
    std::string resFolder {};
#endif

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    VertexArray va;
    VertexBuffer vb(vertices.data(), sizeof(vertices));

    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);
    
    va.AddBuffer(vb, layout);

    IndexBuffer ib(indices.data(), sizeof(indices));

    Shader shader(resFolder + "/shaders/Basic.shader");
    shader.Bind();
    
    // Load texture
    Texture texture(resFolder + "/textures/nene.png");
    texture.Bind();
    shader.SetUniform1i("u_TextureSlot", 0);
    
    // Projection matrix
    glm::mat4 proj = glm::ortho(0.F, 960.F, 0.F, 540.F, -1.F, 1.F);
    glm::mat4 view = glm::translate(glm::mat4(1.F), glm::vec3(100, 0, 0));

    va.Unbind();
    vb.Unbind();
    ib.Unbind();
    shader.Unbind();

    Renderer renderer;
    
    float r {0.5F};
    float increment {0.05F};
    
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    glm::vec3 translation(50, 50, 0);
    /* Loop until the user closes the window */
    while (glfwWindowShouldClose(pWindow) == GLFW_FALSE)
    {
        renderer.Clear();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        /* Draw flow */

        shader.Bind();
        glm::mat4 model = glm::translate(glm::mat4(1.F), translation);
        glm::mat4 mvp = proj * view * model;
        shader.SetUniformMat4f("u_MVP", mvp);
        shader.SetUniform4f("u_Color", {r, 0.5F, 0.5F, 1.0F});

        renderer.Draw(va, ib, shader);
        
        /* Post processing */
        if (r > 1.0F)
            increment = -0.05F;
        else if (r < 0.0F)
            increment = 0.05F;
        r += increment;

        {
            ImGui::SliderFloat3("Translation", &translation.x, 0.0F, 960.0F);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 
                        1000.0F / ImGui::GetIO().Framerate, 
                        ImGui::GetIO().Framerate);
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        /* Swap front and back buffers */
        glfwSwapBuffers(pWindow);

        /* Poll for and process events */
        glfwPollEvents();
    }
}
