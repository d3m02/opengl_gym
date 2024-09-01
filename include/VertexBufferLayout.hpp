#pragma once 

#include <GL/glew.h>

#include <cassert>
#include <vector>


struct VertexBufferElement
{
    unsigned int type;
    int count;
    unsigned char normalized;

    static int GetSizeOfType(unsigned int type)
    {
        switch(type)
        {
        case GL_FLOAT:         return sizeof(GLfloat);
        case GL_UNSIGNED_INT:  return sizeof(GLuint);
        default:               return 0;
        }
    }
};

class VertexBufferLayout
{
public:
    template<typename T>
    void Push(int)
    {
        assert(false);
    }

    [[nodiscard]] inline const std::vector<VertexBufferElement>& GetElements() const { return m_elements; }
    [[nodiscard]] inline int GetStride() const { return m_stride; }

private:
    std::vector<VertexBufferElement> m_elements;
    int m_stride {0};
};

template<>
inline void VertexBufferLayout::Push<float>(int count)
{
    m_elements.push_back({ GL_FLOAT,  count, GL_FALSE });
    m_stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
}

template<>
inline void VertexBufferLayout::Push<unsigned int>(int count)
{
    m_elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
    m_stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
}