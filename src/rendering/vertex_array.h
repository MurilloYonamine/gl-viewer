#pragma once
#include "gl/glew.h"
#include "rendering/vertex_buffer.h"
#include "rendering/vertex_buffer_layout.h"

class VertexArray {
    public:
        VertexArray();
        ~VertexArray();
        VertexArray(const VertexArray&) = delete;
        VertexArray& operator=(VertexArray&& other) noexcept;
        VertexArray(VertexArray&& other) noexcept;

        void Bind();
        void Unbind();

        void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
        
    private:
        GLuint m_RendererID;
};
