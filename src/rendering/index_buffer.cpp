#include "rendering/index_buffer.h"

IndexBuffer::IndexBuffer(const unsigned int *data, unsigned int count) : m_Count(count)
{
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &m_RendererID);
}

IndexBuffer &IndexBuffer::operator=(IndexBuffer &&other) noexcept
{
    if (this != &other)
    {
        glDeleteBuffers(1, &m_RendererID);
        
        m_RendererID = other.m_RendererID;
        m_Count = other.m_Count;

        other.m_RendererID = 0;
        other.m_Count = 0;
    }

    return *this;
}

IndexBuffer::IndexBuffer(IndexBuffer &&other) noexcept : m_RendererID(other.m_RendererID), m_Count(other.m_Count)
{
    other.m_RendererID = 0;
    other.m_Count = 0;
}

void IndexBuffer::Bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void IndexBuffer::Unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
