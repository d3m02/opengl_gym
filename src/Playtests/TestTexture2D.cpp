#include "TestTexture2D.hpp"

#include <imgui.h>
#include <array>

#include "OGGCommon.hpp"
#include "VertexBuffer.hpp"
#include "VertexArray.hpp"
#include "VertexBufferLayout.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Renderer.hpp"


namespace playtest
{

TestTexture2D::TestTexture2D()
    : m_proj (glm::ortho(0.F, 960.F, 0.F, 540.F, -1.F, 1.F))
    , m_view (glm::translate(glm::mat4(1.F), glm::vec3(0, 0, 0)))
{
    std::array vertices { -50.F, -50.F, 0.0F, 0.0F,   // 0
                           50.F, -50.F, 1.0F, 0.0F,   // 1
                           50.F,  50.F, 1.0F, 1.0F,   // 2
                          -50.F,  50.F, 0.0F, 1.0F }; // 3
    
    
    std::array indices { 0U, 1U, 2U,
                         2U, 3U, 0U };
                         
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    m_vertexArray = std::make_unique<VertexArray>();
    m_vertexBuffer = std::make_unique<VertexBuffer>(vertices.data(), sizeof(vertices));

    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);
    
    m_vertexArray->AddBuffer(*m_vertexBuffer, layout);

    m_indexBuffer = std::make_unique<IndexBuffer>(indices.data(), sizeof(indices));

    m_shader = std::make_unique<Shader>(std::string(RES_FOLDER) + "/shaders/Basic.shader");
    m_shader->Bind();

    m_texture = std::make_unique<Texture>(std::string(RES_FOLDER) + "/textures/nene.png");
    m_shader->SetUniform1i("u_TextureSlot", 0);
}

void TestTexture2D::OnUpdate(float)
{
    if (m_colorR > 1.0F)
        m_increment = -0.05F;
    else if (m_colorR < 0.0F)
        m_increment = 0.05F;
    m_colorR += m_increment;
}

void TestTexture2D::OnRender()
{
    GlCall(glClearColor(0.F, 0.F, 0.F, 1.F));
    GlCall(glClear(GL_COLOR_BUFFER_BIT));
    
    Renderer renderer;
    
    m_texture->Bind();

    {
        glm::mat4 model = glm::translate(glm::mat4(1.F), m_translationA);
        glm::mat4 mvp = m_proj * m_view * model;

        m_shader->Bind();
        m_shader->SetUniformMat4f("u_MVP", mvp);
        m_shader->SetUniform4f("u_Color", {m_colorR, 0.5F, 0.5F, 1.0F});

        renderer.Draw(*m_vertexArray, *m_indexBuffer, *m_shader);
    }

    {
        glm::mat4 model = glm::translate(glm::mat4(1.F), m_translationB);
        glm::mat4 mvp = m_proj * m_view * model;

        m_shader->Bind();
        m_shader->SetUniformMat4f("u_MVP", mvp);
        m_shader->SetUniform4f("u_Color", {m_colorR, 0.5F, 0.5F, 1.0F});

        renderer.Draw(*m_vertexArray, *m_indexBuffer, *m_shader);
    }
}

void TestTexture2D::OnImGuiRender()
{
    ImGui::SliderFloat3("m_translationA", &m_translationA.x, 0.0F, 960.0F);
    ImGui::SliderFloat3("m_translationB", &m_translationB.x, 0.0F, 960.0F);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 
                 1000.0F / ImGui::GetIO().Framerate, 
                 ImGui::GetIO().Framerate);
}

}