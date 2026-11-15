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
        VertexBufferLayout() = default;
        unsigned int GetStride() const { return m_Stride; }

        void PushFloat(unsigned int count);

        const std::vector<VertexBufferElement>& GetElements() const { return m_Elements; }

    private:
        std::vector<VertexBufferElement> m_Elements;
        unsigned int m_Stride = 0;
};