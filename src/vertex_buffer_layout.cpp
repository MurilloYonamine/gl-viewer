#include "vertex_buffer_layout.h"

void VertexBufferLayout::PushFloat(unsigned int count)
{
    m_Elements.push_back({GL_FLOAT, count, GL_FALSE});

    m_Stride += count * sizeof(float);
}