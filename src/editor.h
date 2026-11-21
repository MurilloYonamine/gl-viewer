#pragma once

#include "camera.h"
#include "window.h"

class Editor
{
    public:
        Editor(Window &window);
        ~Editor();

        void BeginFrame();
        void EndFrame();
        void OnGUI(Camera &camera, glm::vec3& lightDirection, float& ambientStrength, float& specularStrength);

    private:
        Window &m_Window;
};