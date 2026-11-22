// Created by murillo.gyonamine on 21/11/2026.

#pragma once

#include <glm/glm.hpp>

struct Transform
{
    glm::vec3 position{0.0f};
    glm::vec3 rotation{0.0f};
    glm::vec3 scale{0.01f};

    bool shouldAutoRotate = false;
    glm::mat4 autoRotation{1.0f};
    float autoRotateSpeed = 0.5f; 
    glm::vec3 autoRotateAxis{0.0f, 1.0f, 0.0f};

    void Update(float deltaTime);
    glm::mat4 GetModelMatrix() const;
};
