// Created by murillo.gyonamine on 07/09/2026.

#pragma once

#include "core/window.h"
#include "ui/editor.h"
#include "scene/camera.h"
#include "rendering/shader.h"
#include "scene/model.h"

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
