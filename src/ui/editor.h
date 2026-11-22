#pragma once

#include "scene/camera.h"
#include "core/window.h"
#include "scene/lighting_settings.h"
#include "scene/transform.h"

class Editor
{
    public:
        Editor(Window &window);
        ~Editor();

        void BeginFrame();
        void EndFrame();
        void OnGUI(Camera &camera, LightingSettings& lighting, Transform& transform);

    private:
        Window &m_Window;
};
