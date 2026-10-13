#pragma once

#include <memory>

#include "window.h"
#include "vertex_buffer.h"
#include "vertex_array.h"

class Simulation {
    public:
        Simulation();
        ~Simulation();
        void Update();

    private:
        Window m_Window;
        VertexBuffer m_Vbo;
        VertexArray m_Vao;
        VertexBufferLayout m_Layout;
};