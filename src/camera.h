#pragma once

#include <glm/glm.hpp>

class Camera
{
    public:
        Camera() = default;

        glm::mat4 GetView();
        glm::mat4 GetProjection(float aspectRatio) const;

        float GetFov() const { return m_Fov; }
        void SetFov(float fov);

        float GetYaw() const { return m_Yaw; }
        void SetYaw(float yaw);

        glm::vec3 GetPosition() { return m_Position; }

    private:
        glm::vec3 m_Position{0.0f, 0.0f, 3.0f};
        glm::vec3 m_Target{0.0f, 0.0f, 0.0f};
        glm::vec3 m_Up{0.0f, 1.0f, 0.0f};

        float m_Fov = 45.0f;
        float m_NearPlane = 0.1f;
        float m_FarPlane = 100.0f;

        float m_Distance = 3.0f;
        float m_Yaw = 0.0f; // horizontal angle

        void UpdatePosition();
};