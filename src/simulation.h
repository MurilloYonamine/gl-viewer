#pragma once

#include "window.h"
#include "editor.h"
#include "camera.h"

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
        Editor m_Editor;
        Camera m_Camera;

        VertexBuffer m_Vbo;
        VertexArray m_Vao;
        IndexBuffer m_Ibo;
        VertexBufferLayout m_Layout;
};