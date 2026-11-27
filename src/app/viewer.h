// Created by murillo.gyonamine on 07/09/2026.

#pragma once

#include "core/window.h"
#include "ui/editor.h"

#include "scene/camera.h"
#include "scene/model.h"

#include "rendering/shader.h"
#include "rendering/texture.h"
#include "rendering/material.h"
#include <optional>

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
        Shader m_Shader;
        Material m_Material;
        std::optional<Texture> m_Texture;
        std::optional<Texture> m_SpecularTexture;
        std::optional<Model> m_Model;
        
        LightingSettings m_Lighting;
        Transform m_Transform;

        void RenderScene();
};
