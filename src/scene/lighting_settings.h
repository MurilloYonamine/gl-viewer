// Created by murillo.gyonamine on 21/11/2026.

#pragma once

#include <glm/glm.hpp>

struct LightingSettings
{
    glm::vec3 direction{0.5f, 1.0f, 1.0f};
    float ambientStrength = 0.2f;
    float specularStrength = 0.2f;
};
