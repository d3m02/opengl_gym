#pragma once

class VertexBuffer
{
public:
    VertexBuffer(const void* pData, unsigned int size);
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;
    
private:

    unsigned int m_rendererID;
};