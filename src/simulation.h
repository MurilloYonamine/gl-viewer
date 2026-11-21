#pragma once

#include "window.h"
#include "editor.h"
#include "camera.h"
#include "mesh.h"

#include <memory>
#include <string_view>

class Simulation
{
    public:
        Simulation();
        ~Simulation();
        void Update();

    private:
        Window m_Window;
        Editor m_Editor;
        Camera m_Camera;
        Mesh m_Mesh;

        Mesh LoadMesh(std::string_view path);
};