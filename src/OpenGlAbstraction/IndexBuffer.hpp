#pragma once

class IndexBuffer
{
public:
    IndexBuffer(const unsigned int* pData, unsigned int count);
    ~IndexBuffer();

    void Bind() const;
    void Unbind() const;

    [[nodiscard]] inline unsigned int GetCount() const { return m_count; }
    
private:

    unsigned int m_rendererID;
    unsigned int m_count;
};