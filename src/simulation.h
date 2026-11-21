#pragma once

#include "window.h"
#include "editor.h"
#include "camera.h"
#include "model.h"

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
        Model m_Model;
};