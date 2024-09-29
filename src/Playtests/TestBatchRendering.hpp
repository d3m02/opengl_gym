#pragma once 
#include "TestBase.hpp"

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

class TestBatchRendering : public TestBase
{
public:
    TestBatchRendering();
    ~TestBatchRendering() override = default ;

    void OnUpdate(float) override;
    void OnRender() override;
    void OnImGuiRender() override;

private:
    std::unique_ptr<VertexArray> m_vertexArray;
    std::unique_ptr<IndexBuffer> m_indexBuffer;
    std::unique_ptr<VertexBuffer> m_vertexBuffer;
    std::unique_ptr<Shader> m_shader;
    std::unique_ptr<Texture> m_texture1;
    std::unique_ptr<Texture> m_texture2;

    glm::mat4 m_proj;
    glm::mat4 m_view;
    glm::vec3 m_translationA { 50, 50, 0 };
    glm::vec3 m_translationB { 400, 50, 0 };
};

}