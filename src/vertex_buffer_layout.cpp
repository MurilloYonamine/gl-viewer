#include "vertex_buffer_layout.h"

VertexBufferLayout::VertexBufferLayout() : m_Stride(0)
{
}

unsigned int VertexBufferLayout::GetStride() const
{
    return m_Stride;
}

void VertexBufferLayout::PushFloat(unsigned int count)
{
    m_Elements.push_back({GL_FLOAT, count, GL_FALSE});

    m_Stride += count * sizeof(float);
}

const std::vector<VertexBufferLayout::VertexBufferElement> &VertexBufferLayout::GetElements() const
{
    return m_Elements;
}
