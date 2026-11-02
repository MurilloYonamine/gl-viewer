#pragma once

#include <memory>

#include "window.h"
#include "vertex_buffer.h"
#include "vertex_array.h"
#include "index_buffer.h"

class Simulation {
    public:
        Simulation();
        ~Simulation();
        void Update();

    private:
        Window m_Window;
        VertexBuffer m_Vbo;
        VertexArray m_Vao;
        IndexBuffer m_Ibo;
        VertexBufferLayout m_Layout;
};