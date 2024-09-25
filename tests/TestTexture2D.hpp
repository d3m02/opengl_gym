#pragma once 
#include "TestBase.hpp"

#include <array>
#include <memory>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class VertexArray;
class IndexBuffer;
class Shader;
class Texture;
class VertexBuffer;

namespace playtest
{

class TestTexture2D : public TestBase
{
public:
    TestTexture2D();
    ~TestTexture2D() override = default ;

    void OnUpdate(float) override;
    void OnRender() override;
    void OnImGuiRender() override;

private:
    std::unique_ptr<VertexArray> m_vertexArray;
    std::unique_ptr<IndexBuffer> m_indexBuffer;
    std::unique_ptr<VertexBuffer> m_vertexBuffer;
    std::unique_ptr<Shader> m_shader;
    std::unique_ptr<Texture> m_texture;

    float m_colorR { 0.5F };
    float m_increment { 0.05F };
    
    glm::mat4 m_proj;
    glm::mat4 m_view;
    glm::vec3 m_translationA { 50, 50, 0 };
    glm::vec3 m_translationB { 400, 50, 0 };
};

}