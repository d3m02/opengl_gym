#include "TestBatchRendering.hpp"

#include <imgui.h>
#include <array>

#include "OGGCommon.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"
#include "Renderer.hpp"
#include "Texture.hpp"


namespace playtest
{

struct Vertex
{
    std::array<float, 3> positions;
    std::array<float, 4> color;
    std::array<float, 2> textureCoord;
    float textureSlot;
};

TestBatchRendering::TestBatchRendering()
    : m_proj (glm::ortho(0.F, 960.F, 0.F, 540.F, -1.F, 1.F))
    , m_view (glm::translate(glm::mat4(1.F), glm::vec3(0, 0, 0)))
{
    
    std::array indices { 0U, 1U, 2U, 2U, 3U, 0U,
                         4U, 5U, 6U, 6U, 7U, 4U };
                         
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    m_vertexArray = std::make_unique<VertexArray>();
    m_vertexBuffer = std::make_unique<VertexBuffer>(nullptr, sizeof(Vertex) * 8);

    VertexBufferLayout layout;
    layout.Push<float>(3);  // vertex possition
    layout.Push<float>(4);  // vertex color
    layout.Push<float>(2);  // vertex texture coord
    layout.Push<float>(1);  // vertex texture slot
    
    m_vertexArray->AddBuffer(*m_vertexBuffer, layout);

    m_indexBuffer = std::make_unique<IndexBuffer>(indices.data(), sizeof(indices));

    m_shader = std::make_unique<Shader>(std::string(RES_FOLDER) + "/shaders/Quad.shader");
    m_shader->Bind();

    m_texture1 = std::make_unique<Texture>(std::string(RES_FOLDER) + "/textures/nene.png");
    m_texture2 = std::make_unique<Texture>(std::string(RES_FOLDER) + "/textures/nene2.png");

    m_shader->SetUniform1iv("u_Textures", {0, 1}); 
}

void TestBatchRendering::OnUpdate(float)
{
    static float m_color { 0.5F };
    static float m_increment { 0.05F };
    if (m_color > 1.0F)
        m_increment = -0.05F;
    else if (m_color < 0.0F)
        m_increment = 0.05F;
    m_color += m_increment;

    std::array<Vertex, 8> oldvertices {{ 
        { .positions =    {-50.F, -50.F, 0.0F}, 
          .color =        {m_color, 0.6F, 0.96F, 1.0F}, 
          .textureCoord = {0.0F, 0.0F}, 
          .textureSlot =  0.0F },
        { .positions =    { 50.F, -50.F, 0.0F}, 
          .color =        {0.18F, m_color, 0.16F, 1.0F}, 
          .textureCoord = {1.0F, 0.0F}, 
          .textureSlot =  0.0F }, 
        { .positions =    { 50.F,  50.F, 0.0F}, 
          .color =        {0.78F, 0.6F, m_color, 1.0F}, 
          .textureCoord = {1.0F, 1.0F},
          .textureSlot =  0.0F }, 
        { .positions =    {-50.F,  50.F, 0.0F}, 
          .color =         {0.18F, 0.6F, 0.96F, 1.0F}, 
          .textureCoord =  {0.0F, 1.0F},
          .textureSlot =   0.0F },

         { .positions =    {150.F, 150.F, 0.0F}, 
           .color =        {1.F, m_color, 0.24F, 1.0F}, 
           .textureCoord = {0.0F, 0.0F}, 
           .textureSlot =  1.0F },   
         { .positions =    { 50.F, 150.F, 0.0F}, 
           .color =        {m_color, 0.93F, 0.94F, 1.0F}, 
           .textureCoord = {1.0F, 0.0F}, 
           .textureSlot =  1.0F },   
         { .positions =    { 50.F,  50.F, 0.0F}, 
           .color =        {1.F, m_color, 0.84F, 1.0F}, 
           .textureCoord = {1.0F, 1.0F}, 
           .textureSlot =  1.0F },   
         { .positions =    {150.F,  50.F, 0.0F}, 
           .color =        {0.F, 0.93F, m_color, 1.0F}, 
           .textureCoord = {0.0F, 1.0F}, 
           .textureSlot =  1.0F } 
         }};

        m_vertexBuffer->pushData(oldvertices.data(), sizeof(oldvertices));
}

void TestBatchRendering::OnRender()
{
    GlCall(glClearColor(0.F, 0.F, 0.F, 1.F));
    GlCall(glClear(GL_COLOR_BUFFER_BIT));
    
    Renderer renderer;
    
    {
        glm::mat4 model = glm::translate(glm::mat4(1.F), m_translationA);
        glm::mat4 mvp = m_proj * m_view * model;

        m_shader->Bind();
        m_shader->SetUniformMat4f("u_MVP", mvp);
        m_texture1->Bind(0);
        m_texture2->Bind(1);

        renderer.Draw(*m_vertexArray, *m_indexBuffer, *m_shader);
    }
}

void TestBatchRendering::OnImGuiRender()
{
    ImGui::SliderFloat3("m_translationA", &m_translationA.x, 0.0F, 960.0F);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 
                 1000.0F / ImGui::GetIO().Framerate, 
                 ImGui::GetIO().Framerate);
}

}