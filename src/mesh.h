#pragma once

#include <vector>

#include "vertex_array.h"
#include "vertex_buffer.h"
#include "index_buffer.h"

class Mesh
{
    public:
        Mesh(const std::vector<float> &vertices, const std::vector<unsigned int> &indices);
        Mesh(const Mesh &) = delete;
        Mesh &operator=(const Mesh &) = delete;

        void Draw();

    private:
        VertexArray m_Vao;
        VertexBuffer m_Vbo;
        IndexBuffer m_Ibo;
};