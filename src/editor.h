#pragma once

#include "camera.h"

class Editor
{
    public:
        void OnGUI(Camera &camera, glm::vec3& lightDirection, float& ambientStrength);
};