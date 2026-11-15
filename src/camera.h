#pragma once

#include <glm/glm.hpp>

class Camera
{
    public:
        Camera();

        glm::mat4 GetView() const;
        glm::mat4 GetProjection(float aspectRatio) const;
        float GetFov() const;

        void SetFov(float fov);

    private:
        glm::vec3 m_Position;
        glm::vec3 m_Target;
        glm::vec3 m_Up;

        float m_Fov;
        float m_NearPlane;
        float m_FarPlane;
};