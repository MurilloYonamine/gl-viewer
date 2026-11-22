#pragma once
#include <vector>

class VertexBufferLayout {
    struct VertexBufferElement
    {
        unsigned int type;
        unsigned int count;
        unsigned char normalized;
        size_t offset;
    };

    public:
        VertexBufferLayout(size_t stride);
        unsigned int GetStride() const { return m_Stride; }

        void PushFloat(unsigned int count, size_t offset);

        const std::vector<VertexBufferElement>& GetElements() const { return m_Elements; }

    private:
        std::vector<VertexBufferElement> m_Elements;
        unsigned int m_Stride = 0;
};
