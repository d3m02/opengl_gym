#include "OpenGlGym.hpp"

#include <iostream>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <ext/matrix_clip_space.hpp>
#include <ext/matrix_transform.hpp>
#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>


#include "OGGCommon.hpp"
#include "Renderer.hpp"

#include "TestMenu.hpp"
#include "TestClearColor.hpp"
#include "TestTexture2D.hpp"

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

    pWindow = glfwCreateWindow(960, 540, "OpenGL gym", nullptr, nullptr);
    if (!pWindow)
    {
        return false;
    }

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

    // During init, enable debug output
   // glEnable              ( GL_DEBUG_OUTPUT );
   // glDebugMessageCallback( MessageCallback, 0 );

    return m_initilized;
}

void OpenGlGym::Run()
{
    if (!m_initilized)
        return;

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    Renderer renderer;
    playtest::TestBase* pCurrTest {};
    auto* pTestMenu = new playtest::TestMenu(pCurrTest);
    pCurrTest = pTestMenu;

    pTestMenu->RegisterTest<playtest::TestClearColor>("Clear Color");
    pTestMenu->RegisterTest<playtest::TestTexture2D>("Render texture");
    
    while (glfwWindowShouldClose(pWindow) == GLFW_FALSE)
    {
        GlCall(glClearColor(0.F, 0.F, 0.F, 1.F));
        renderer.Clear();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (pCurrTest)
        {
            pCurrTest->OnUpdate(0.F);
            pCurrTest->OnRender();
            ImGui::Begin("Test");
            if (pCurrTest != pTestMenu && ImGui::Button("<-"))
            {
                delete pCurrTest;
                pCurrTest = pTestMenu;
            }
            pCurrTest->OnImGuiRender();
            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
        glfwSwapBuffers(pWindow);
        glfwPollEvents();
    }
    delete pCurrTest;
    if (pCurrTest != pTestMenu)
        delete pTestMenu;
}
