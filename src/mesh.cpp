#include "mesh.h"

Mesh::Mesh(const std::vector<float> &vertices, const std::vector<unsigned int> &indices)
    : m_Vbo(vertices.data(), vertices.size() * sizeof(float)),
      m_Ibo(indices.data(), indices.size())
{
    VertexBufferLayout layout;

    layout.PushFloat(3); // Position
    layout.PushFloat(3); // Color

    m_Vao.AddBuffer(m_Vbo, layout);
    m_Vao.Unbind();
}

void Mesh::Draw()
{
    m_Vao.Bind();
    glDrawElements(
        GL_TRIANGLES,
        static_cast<GLsizei>(m_Ibo.GetCount()),
        GL_UNSIGNED_INT,
        nullptr
    );
}