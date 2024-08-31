#include "VertexArray.hpp"

#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_rendererID);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_rendererID);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) const
{
    Bind();
    vb.Bind();
    const auto& elements = layout.GetElements();
    unsigned int offset {0};
    for (int i = 0; i < elements.size(); i++)
    {
        const auto& element = elements[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.count, element.type, 
                              element.normalized, layout.GetStride(), 
                              reinterpret_cast<const void*>(offset));
        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }
    Unbind();
}

void VertexArray::Bind() const
{
    glBindVertexArray(m_rendererID);
}

void VertexArray::Unbind() const
{
    glBindVertexArray(0);
}