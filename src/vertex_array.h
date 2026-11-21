#pragma once
#include "gl/glew.h"
#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"

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