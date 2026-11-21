#pragma once

#include "camera.h"
#include "window.h"
#include "lighting_settings.h"

class Editor
{
    public:
        Editor(Window &window);
        ~Editor();

        void BeginFrame();
        void EndFrame();
        void OnGUI(Camera &camera, LightingSettings& lighting);

    private:
        Window &m_Window;
};