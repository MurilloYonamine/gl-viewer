// Created by murillo.gyonamine on 14/11/2026.

#pragma once

#include "scene/camera.h"
#include "core/window.h"
#include "scene/lighting_settings.h"
#include "scene/transform.h"
#include "../rendering/material.h"

class Editor
{
    public:
        Editor(Window &window);
        ~Editor();

        void BeginFrame();
        void EndFrame();
        void OnGUI(Camera &camera, LightingSettings& lighting, Transform& transform, Material& material);

    private:
        Window &m_Window;
};
