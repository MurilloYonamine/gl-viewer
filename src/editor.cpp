#include "editor.h"
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

void Editor::OnGUI(Camera &camera)
{
    ImGui::Begin("GL Viewer");
    if (ImGui::CollapsingHeader("Camera"))
    {
        float fov = camera.GetFov();
        if (ImGui::SliderFloat("FOV", &fov, 20.0f, 100.0f))
        {
            camera.SetFov(fov);
        }

        float yaw = glm::degrees(camera.GetYaw());
        if (ImGui::SliderFloat("Yaw", &yaw, 0.0f, 360.0f, "%.0f"))
        {
            camera.SetYaw(glm::radians(yaw));
        }
    }

    ImGui::End();
}