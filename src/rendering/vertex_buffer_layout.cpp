// Created by murillo.gyonamine on 07/09/2026.

#include "rendering/vertex_buffer_layout.h"
#include <GL/glew.h>

VertexBufferLayout::VertexBufferLayout(size_t stride) : m_Stride(stride)
{
}

void VertexBufferLayout::PushFloat(unsigned int count, size_t offset)
{
    m_Elements.push_back({GL_FLOAT, count, GL_FALSE, offset});
}
