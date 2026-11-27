// Created by murillo.gyonamine on 07/09/2026.
#pragma once

#include <glm/glm.hpp>
#include "texture.h"

struct Material
{
    glm::vec3 baseColor{1.0f, 1.0f, 1.0f};
    glm::vec3 ambient{1.0};
    glm::vec3 diffuse{1.0};
    glm::vec3 specular{0.0, 1.0f, 0.0f};
    float shininess = 32.0f;

    Texture *texture = nullptr;
    Texture* specularMap = nullptr;
};