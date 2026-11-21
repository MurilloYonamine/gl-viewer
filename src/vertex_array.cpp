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

VertexArray &VertexArray::operator=(VertexArray &&other) noexcept
{
    if (this != &other)
    {
        glDeleteVertexArrays(1, &m_RendererID);
        m_RendererID = other.m_RendererID;
        other.m_RendererID = 0;
    }

    return *this;
}

VertexArray::VertexArray(VertexArray &&other) noexcept : m_RendererID(other.m_RendererID)
{
    other.m_RendererID = 0;
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
    unsigned int count, type, normalized, offset;
    unsigned int index = 0;

    Bind();
    vbo.Bind();

    for (const auto& element : layout.GetElements())
    {
        count = element.count;
        normalized = element.normalized;
        type = element.type;
        offset = element.offset;

        glVertexAttribPointer(index, count, type, normalized, stride, reinterpret_cast<const void *>(static_cast<std::uintptr_t>(offset)));
        
        glEnableVertexAttribArray(index);
        index++;
    }
}
