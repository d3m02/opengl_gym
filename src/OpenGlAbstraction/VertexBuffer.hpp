#pragma once

class VertexBuffer
{
public:
    VertexBuffer(const void* pData, unsigned int size);
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;

    void pushData(const void* pData, unsigned int size) const;
    
private:

    unsigned int m_rendererID;
    bool m_isDynamic {true};
};