#pragma once
#include "gl/glew.h"

class VertexBuffer {
    public:
        VertexBuffer(const unsigned int* data, unsigned int size);
        ~VertexBuffer();

        void Bind();
        void Unbind();

    private:
        GLuint m_RendererID;
};