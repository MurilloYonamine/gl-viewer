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

void VertexArray::AddBuffer(const VertexBuffer &vbo, const VertexBufferLayout &layout)
{
    unsigned int stride = layout.GetStride();
    unsigned int count, type, normalized;

    unsigned int index = 0;
    unsigned int offset = 0;

    vbo.Bind();

    for(const auto element : layout.GetElements()) {
        count = element.count;
        normalized = element.normalized;
        type = element.type;
        
        glVertexAttribPointer(index, count, type, normalized, stride, (void*)(offset * sizeof(float)));
        glEnableVertexAttribArray(index);
        
        offset += count;
        index++;
    }
}
