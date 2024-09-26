#include "IndexBuffer.hpp"

#include "OGGCommon.hpp"

IndexBuffer::IndexBuffer(const unsigned int* pData, unsigned int count)
    : m_count(count)
{
    glGenBuffers(1, &m_rendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
                 static_cast<GLsizeiptr>(count * sizeof(unsigned int)), 
                 pData, 
                 GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &m_rendererID);
}

void IndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
}

void IndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

    