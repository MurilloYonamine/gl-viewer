#pragma once

class IndexBuffer {
    public:
        IndexBuffer(const unsigned int* data, unsigned int count);
        ~IndexBuffer();

        void Bind();
        void Unbind();

        unsigned int GetCount();

    private:
        GLuint m_RendererID;
        unsigned int m_Count;
}