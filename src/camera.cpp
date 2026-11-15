#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 Camera::GetView() const
{
    glm::vec3 position;

    position.x = m_Target.x + m_Distance * glm::sin(m_Yaw);
    position.y = m_Target.y;
    position.z = m_Target.z + m_Distance * glm::cos(m_Yaw);

    glm::mat4 view = glm::lookAt(position, m_Target, m_Up);

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
}
