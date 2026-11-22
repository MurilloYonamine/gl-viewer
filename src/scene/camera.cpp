// Created by murillo.gyonamine on 14/11/2026.

#include "scene/camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include "camera.h"


glm::mat4 Camera::GetView()
{
    glm::mat4 view = glm::lookAt(m_Position, m_Target, m_Up);
    return view;
}

glm::mat4 Camera::GetProjection(float aspectRatio) const
{
    glm::mat4 projection = glm::perspective(glm::radians(m_Fov), aspectRatio, 0.1f, 100.0f);
    return projection;
}

void Camera::SetFov(float fov)
{
    m_Fov = glm::clamp(fov, 20.0f, 100.0f);
}

void Camera::SetYaw(float yaw)
{
    m_Yaw = yaw;
    UpdatePosition();
}

void Camera::SetDistance(float distance)
{
    m_Distance = glm::clamp(distance, 0.5f, 20.0f);
    UpdatePosition();
}

void Camera::UpdatePosition()
{
    m_Position.x = m_Target.x + m_Distance * glm::sin(m_Yaw);
    m_Position.y = m_Target.y;
    m_Position.z = m_Target.z + m_Distance * glm::cos(m_Yaw);
}
