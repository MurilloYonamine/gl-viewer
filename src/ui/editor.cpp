// Created by murillo.gyonamine on 14/11/2026.

#include "ui/editor.h"
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

void Editor::OnGUI(Camera &camera, LightingSettings &lighting, Transform &transform, Material &material)
{
    ImGui::Begin("GL Viewer");

    if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::DragFloat3("Position", glm::value_ptr(transform.position), 0.1f);
        ImGui::DragFloat3("Rotation", glm::value_ptr(transform.rotation), 0.1f);
        ImGui::DragFloat3("Scale", glm::value_ptr(transform.scale), 0.1f);
        ImGui::Checkbox("Auto Rotate", &transform.shouldAutoRotate);
        if (transform.shouldAutoRotate)
        {
            ImGui::SliderFloat("Rotation Speed", &transform.autoRotateSpeed, 0.0f, 1.0f, "Speed: %.1f");
            ImGui::DragFloat3("Rotation Axis", glm::value_ptr(transform.autoRotateAxis), -1.0f, 1.0f);
        }
    }

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    if (ImGui::CollapsingHeader("Camera"))
    {
        float zoom = camera.GetDistance();
        if (ImGui::SliderFloat("Zoom", &zoom, 0.5f, 20.0f, "%.0f"))
        {
            camera.SetDistance(zoom);
        }

        float yaw = glm::degrees(camera.GetYaw());
        if (ImGui::SliderFloat("Rotate Camera", &yaw, 0.0f, 360.0f, "%.0f"))
        {
            camera.SetYaw(glm::radians(yaw));
        }
    }

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    if (ImGui::CollapsingHeader("Lighting"))
    {
        ImGui::DragFloat3("Light Direction", glm::value_ptr(lighting.direction), 0.1f);
        ImGui::SliderFloat("Ambient Strength", &lighting.ambientStrength, 0.0f, 1.0f);
        ImGui::SliderFloat("Specular Strength", &lighting.specularStrength, 0.0f, 1.0f);
    }
    if (ImGui::CollapsingHeader("Material"))
    {
        ImGui::ColorEdit3("Base Color", glm::value_ptr(material.baseColor));
        ImGui::ColorEdit3("Ambient", glm::value_ptr(material.ambient), ImGuiColorEditFlags_Float);
        ImGui::ColorEdit3("Diffuse", glm::value_ptr(material.diffuse), ImGuiColorEditFlags_Float);
        ImGui::ColorEdit3("Specular", glm::value_ptr(material.specular), ImGuiColorEditFlags_Float);
        ImGui::SliderFloat("Shininess", &material.shininess, 1.0f, 256.0f);
    }
    ImGui::End();
}
