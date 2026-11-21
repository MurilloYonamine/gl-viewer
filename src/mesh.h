#pragma once

#include <vector>

#include "vertex_array.h"
#include "vertex_buffer.h"
#include "index_buffer.h"
#include "vertex.h"

class Mesh
{
    public:
        Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices);

        Mesh(const Mesh &) = delete;
        Mesh &operator=(const Mesh &) = delete;

        Mesh(Mesh &&other) noexcept = default;
        Mesh &operator=(Mesh &&other) noexcept = default;

        void Draw();

    private:
        VertexArray m_Vao;
        VertexBuffer m_Vbo;
        IndexBuffer m_Ibo;
};