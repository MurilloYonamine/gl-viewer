// Created by murillo.gyonamine on 21/11/2026.

#pragma once

#include <vector>

#include "rendering/vertex_array.h"
#include "rendering/vertex_buffer.h"
#include "rendering/index_buffer.h"
#include "rendering/vertex.h"

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
