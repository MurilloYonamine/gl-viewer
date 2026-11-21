#pragma once

#include "window.h"
#include "editor.h"
#include "camera.h"
#include "shader.h"
#include "model.h"

class Viewer
{
    public:
        Viewer();
        ~Viewer() = default;
        void Update();

        
    private:
        Window m_Window;
        Editor m_Editor;
        Camera m_Camera;
        Model m_Model;
        Shader m_Shader;
        
        LightingSettings m_Lighting;
        Transform m_Transform;

        void RenderScene();
};