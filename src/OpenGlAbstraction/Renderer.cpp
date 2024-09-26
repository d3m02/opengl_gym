#include "Renderer.hpp"

#include "OGGCommon.hpp"

#include "IndexBuffer.hpp"
#include "Shader.hpp"
#include "VertexArray.hpp"

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    va.Bind();  
    ib.Bind();
    shader.Bind();
    GlCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);
}