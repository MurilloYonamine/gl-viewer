#include "editor.h"
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <glm/gtc/type_ptr.hpp>

void Editor::OnGUI(Camera &camera, glm::vec3 &lightDirection, float &ambientStrength)
{
    ImGui::Begin("GL Viewer");
    if (ImGui::CollapsingHeader("Camera"))
    {
        float fov = camera.GetFov();
        if (ImGui::SliderFloat("Zoom", &fov, 20.0f, 100.0f))
        {
            camera.SetFov(fov);
        }

        float yaw = glm::degrees(camera.GetYaw());
        if (ImGui::SliderFloat("Rotation", &yaw, 0.0f, 360.0f, "%.0f"))
        {
            camera.SetYaw(glm::radians(yaw));
        }
    }

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    if (ImGui::CollapsingHeader("Lighting"))
    {
        ImGui::SliderFloat3("Light Direction", glm::value_ptr(lightDirection), -1.0f, 1.0f);
        ImGui::SliderFloat("Ambient Strength", &ambientStrength, 0.0f, 1.0f);
    }

    ImGui::End();
}