#pragma once
#include "gl/glew.h"

class VertexBuffer {
    public:
        VertexBuffer(const void* data, unsigned int size);
        ~VertexBuffer();
        VertexBuffer(const VertexBuffer&) = delete;
        VertexBuffer& operator=(VertexBuffer&& other) noexcept;
        VertexBuffer(VertexBuffer&& other) noexcept;

        void Bind() const;
        void Unbind() const;

    private:
        GLuint m_RendererID;
};
