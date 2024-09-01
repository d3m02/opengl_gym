#include "Texture.hpp"

#include <iostream>
#include <filesystem>

#include <stb_image.h>

#include "Common.hpp"

Texture::Texture(const std::string& path)
    : m_filePath(path)
{
    stbi_set_flip_vertically_on_load(1);
    m_localBuffer = stbi_load(path.c_str(), &m_width, &m_height, &m_bpp, 4);

    if (!m_localBuffer)
    {
        const std::filesystem::path fsPath {m_filePath};
        if (!std::filesystem::exists(fsPath))
            std::cout << "Files '" << m_filePath << "' not exist\n";
        else 
            std::cout << "Failed to load texture: no data returned from stbi\n";
        return; 
    }

    GlCall(glGenTextures(1, &m_rendererID));
    Bind();

    // Minification filter
    GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    // Magnification filter
    GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    // Horizontal (WRAP_S) Clamp mode (not extend area)
    GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    // vertical (WRAP_T) clamp
    GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    GlCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer));
    Unbind();

    if (m_localBuffer)
        stbi_image_free(m_localBuffer); 
}

Texture::~Texture()
{
    GlCall(glDeleteTextures(1, &m_rendererID));
}

void Texture::Bind(unsigned int slot) const
{
    GlCall(glActiveTexture(GL_TEXTURE0 + slot));
    GlCall(glBindTexture(GL_TEXTURE_2D, m_rendererID));
}

void Texture::Unbind() const
{
    GlCall(glBindTexture(GL_TEXTURE_2D, 0));
}
