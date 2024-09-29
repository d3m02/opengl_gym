#include "VertexBuffer.hpp"

#include "OGGCommon.hpp"

VertexBuffer::VertexBuffer(const void* pData, unsigned int size)
{
    glGenBuffers(1, &m_rendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);

    m_isDynamic = pData == nullptr; 
    if (m_isDynamic)
        glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(size), pData, GL_DYNAMIC_DRAW);
    else 
        glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(size), pData, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_rendererID);
}

void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
}

void VertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::pushData(const void* pData, unsigned int size) const
{
    if (!m_isDynamic)
    {
        LogInfo("Can't push data into non dynamic buffer");
        return;    
    }
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, pData);
}

