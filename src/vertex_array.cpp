#include "vertex_array.h"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_RendererID);
    glBindVertexArray(m_RendererID);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::Bind()
{
    glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind()
{
    glBindVertexArray(0);
}
