#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera()
    : m_Position(0.0f, 0.0f, 3.0f),
      m_Target(0.0f, 0.0f, 0.0f),
      m_Up(0.0f, 1.0f, 0.0f),
      m_Fov(45.0f),
      m_NearPlane(0.1f),
      m_FarPlane(100.0f)
{
}

glm::mat4 Camera::GetView() const
{
    glm::mat4 view = glm::lookAt(
        glm::vec3(0.0f, 0.0f, 3.0f), // camera position
        glm::vec3(0.0f, 0.0f, 0.0f), // point to be observed
        glm::vec3(0.0f, 1.0f, 0.0f)  // direction up
    );
    return view;
}

glm::mat4 Camera::GetProjection(float aspectRatio) const
{
    glm::mat4 projection = glm::perspective(glm::radians(m_Fov), aspectRatio, 0.1f, 100.0f);
    return projection;
}

float Camera::GetFov() const
{
    return m_Fov;
}

void Camera::SetFov(float fov)
{
    m_Fov = glm::clamp(fov, 20.0f, 100.0f);
}
