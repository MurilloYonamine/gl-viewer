// Created by murillo.gyonamine on 22/11/2026.

#pragma once

#include <string>
#include <gl/glew.h>

class Texture {
    public:
        Texture(const std::string& filepath);
        ~Texture();
        Texture(const Texture&) = delete;
        Texture& operator=(const Texture&) = delete;

        void Bind() const;
        void Unbind() const;

    private:
        GLuint m_RendererID = 0;

        int m_Width;
        int m_Height;
        int m_Channels;
};