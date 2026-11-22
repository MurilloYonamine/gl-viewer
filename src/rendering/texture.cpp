// Created by murillo.gyonamine on 22/11/2026.

#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <stdexcept>
#include <iostream>

Texture::Texture(const std::string &filepath)
{
    stbi_set_flip_vertically_on_load(true);
    
    unsigned char *texture = stbi_load(filepath.data(), &m_Width, &m_Height, &m_Channels, 0);

    if (texture == nullptr)
    {
        throw std::runtime_error("Failed to open texture file: " + filepath);
    }

    std::string channelName = (m_Channels == 4) ? "RGBA" : "RGB";

    std::cout << "Name: " << filepath << '\n';
    std::cout << "Width: " << m_Width << '\n';
    std::cout << "Height: " << m_Height << '\n';
    std::cout << "Channels: " << channelName << '\n';

    glGenTextures(1, &m_RendererID);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Set pixel alignment to 1 byte

    GLenum format = (m_Channels == 4) ? GL_RGBA : GL_RGB;
    GLenum internalFormat = (m_Channels == 4) ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, texture);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 4); // Reset pixel alignment to default (4 bytes)

    // Wrapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Mipmaps
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(texture);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_RendererID);
}

void Texture::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

void Texture::Unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
