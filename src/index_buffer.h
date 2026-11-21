#pragma once
#include "gl/glew.h"

class IndexBuffer
{
    public:
        IndexBuffer(const unsigned int *data, unsigned int count);
        ~IndexBuffer();
        IndexBuffer(const IndexBuffer &) = delete;
        IndexBuffer &operator=(IndexBuffer &&other) noexcept;
        IndexBuffer(IndexBuffer &&other) noexcept;

        void Bind();
        void Unbind();

        unsigned int GetCount() const { return m_Count; }

    private:
        GLuint m_RendererID;
        unsigned int m_Count;
};