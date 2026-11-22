// Created by murillo.gyonamine on 21/11/2026.

#include "rendering/mesh.h"

Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices)
    : m_Vbo(vertices.data(), vertices.size() * sizeof(Vertex)),
      m_Ibo(indices.data(), indices.size())
{
    VertexBufferLayout layout(sizeof(Vertex));

    layout.PushFloat(3, offsetof(Vertex, position));
    layout.PushFloat(3, offsetof(Vertex, color));
    layout.PushFloat(3, offsetof(Vertex, normal));
    layout.PushFloat(2, offsetof(Vertex, texCoords));

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
