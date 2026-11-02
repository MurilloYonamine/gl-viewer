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
    std::size_t offset = 0;

    Bind();
    vbo.Bind();

    for(const auto element : layout.GetElements()) {
        count = element.count;
        normalized = element.normalized;
        type = element.type;
        
        glVertexAttribPointer(index, count, type, normalized, stride, reinterpret_cast<const void*>(offset));
        glEnableVertexAttribArray(index);
        
        offset += count * sizeof(float);
        index++;
    }
}
