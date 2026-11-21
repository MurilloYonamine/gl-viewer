#include "editor.h"
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <glm/gtc/type_ptr.hpp>

Editor::Editor(Window &window) : m_Window(window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(m_Window.GetNativeWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 460");
}

Editor::~Editor()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Editor::BeginFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Editor::EndFrame()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Editor::OnGUI(Camera &camera, LightingSettings &lighting, Transform &transform)
{
    ImGui::Begin("GL Viewer");

    if (ImGui::CollapsingHeader("Transform"))
    {
        ImGui::SliderFloat3("Position", glm::value_ptr(transform.position), -10.0f, 10.0f);
        ImGui::SliderFloat3("Rotation", glm::value_ptr(transform.rotation), -180.0f, 180.0f);
        ImGui::SliderFloat3("Scale", glm::value_ptr(transform.scale), 0.1f, 10.0f);
        ImGui::Checkbox("Auto Rotate", &transform.shouldAutoRotate);
        if (transform.shouldAutoRotate)
        {
            ImGui::SliderFloat("Rotation Speed", &transform.autoRotateSpeed, 0.0f, 1.0f, "Speed: %.1f");
            ImGui::SliderFloat3("Rotation Axis", glm::value_ptr(transform.autoRotateAxis), -1.0f, 1.0f);
        }
    }

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

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
        ImGui::SliderFloat3("Light Direction", glm::value_ptr(lighting.direction), -1.0f, 1.0f);
        ImGui::SliderFloat("Ambient Strength", &lighting.ambientStrength, 0.0f, 1.0f);
        ImGui::SliderFloat("Specular Strength", &lighting.specularStrength, 0.0f, 1.0f);
    }

    ImGui::End();
}