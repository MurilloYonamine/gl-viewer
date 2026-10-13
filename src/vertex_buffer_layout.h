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
        unsigned int GetStride() const;

        void PushFloat(unsigned int count);

        const std::vector<VertexBufferElement>& GetElements() const;

    private:
        std::vector<VertexBufferElement> m_Elements;
        unsigned int m_Stride;
};