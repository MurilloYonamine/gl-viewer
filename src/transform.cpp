#include "transform.h"

#include <glm/gtc/matrix_transform.hpp>

void Transform::Update(float deltaTime)
{
    if (!shouldAutoRotate)
        return;

    if (glm::length(autoRotateAxis) < 0.0001f)
        return;

    autoRotation = glm::rotate(autoRotation, autoRotateSpeed * deltaTime, glm::normalize(autoRotateAxis));
}

glm::mat4 Transform::GetMatrix() const
{
    glm::mat4 model(1.0f);

    // Translation
    model = glm::translate(model, position);

    // Rotation
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    // Auto Rotation
    model = model * autoRotation;

    // Scale
    model = glm::scale(model, scale);

    return model;
}