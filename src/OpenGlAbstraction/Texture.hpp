#pragma once

#include <string>

class Texture
{
public:
    explicit Texture(const std::string& path);
    ~Texture();

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

    [[nodiscard]] inline int GetHeight() const { return m_height; }
    [[nodiscard]] inline int GetWidth() const { return m_width; }

private:
    unsigned int m_rendererID {0};
    std::string m_filePath;
    unsigned char* m_localBuffer {nullptr};
    int m_width {0};
    int m_height {0};
    int m_bpp {0};
};
