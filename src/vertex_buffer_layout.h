#pragma once
#include <vector>
#include "gl/glew.h"

class VertexBufferLayout {
    struct VertexBufferElement
    {
        unsigned int type;
        unsigned int count;
        unsigned char normalized;
    };

    public:
        VertexBufferLayout();
        unsigned int GetStride();

        void PushFloat(unsigned int count);

        std::vector<VertexBufferElement>& GetElements();

    private:
        std::vector<VertexBufferElement> m_Elements;
        unsigned int m_Stride;
};