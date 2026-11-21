#pragma once

#include "window.h"
#include "editor.h"
#include "camera.h"
#include "model.h"

class Viewer
{
    public:
        Viewer();
        ~Viewer();
        void Update();

    private:
        Window m_Window;
        Editor m_Editor;
        Camera m_Camera;
        Model m_Model;
};