#pragma once
#include "gl/glew.h"

class VertexArray {
    public:
        VertexArray();
        ~VertexArray();

        void Bind();
        void Unbind();
        
    private:
        GLuint m_RendererID;
};