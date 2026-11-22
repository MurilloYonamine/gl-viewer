// Created by murillo.gyonamine on 14/11/2026.

#include "ui/editor.h"
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <glm/gtc/type_ptr.hpp>
#include <ImGuiFileDialog.h>
#include <iostream>

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

FileSelection Editor::OnGUI(Camera &camera, LightingSettings &lighting, Transform &transform, Material &material)
{
    FileSelection selection;

    if (ImGui::Begin("GL Viewer"))
    {
        DrawModelSection();
        ImGui::Spacing();
        DrawTransformSection(transform);
        ImGui::Spacing();
        DrawCameraSection(camera);
        ImGui::Spacing();
        DrawLightingSection(lighting);
        ImGui::Spacing();
        DrawMaterialSection(material);
    }

    ImGui::End();

    HandleFileDialogs(selection);

    return selection;
}

void Editor::DrawModelSection()
{
    if (!ImGui::CollapsingHeader("Model", ImGuiTreeNodeFlags_DefaultOpen))
        return;

    if (ImGui::Button("Open Model"))
    {
        IGFD::FileDialogConfig config;
        config.path = ".";

        ImGuiFileDialog::Instance()->OpenDialog("OpenModelDialog", "Select a 3D Model", ".obj,.fbx,.gltf,.glb", config);
    }

    ImGui::SameLine();
    ImGui::SetNextItemWidth(-1.0f);
    ImGui::InputText("##ModelPath", m_ModelPath.data(), m_ModelPath.size(), ImGuiInputTextFlags_ReadOnly);

    if (ImGui::Button("Open Texture"))
    {
        IGFD::FileDialogConfig config;
        config.path = ".";

        ImGuiFileDialog::Instance()->OpenDialog("OpenTextureDialog", "Select a Texture", ".png,.jpg", config);
    }

    ImGui::SameLine();
    ImGui::SetNextItemWidth(-1.0f);
    ImGui::InputText("##TexturePath", m_TexturePath.data(), m_TexturePath.size(), ImGuiInputTextFlags_ReadOnly);
}

void Editor::HandleFileDialogs(FileSelection &selection)
{
    auto *dialog = ImGuiFileDialog::Instance();

    if (dialog->Display("OpenModelDialog", ImGuiWindowFlags_NoCollapse, ImVec2(900, 550), ImVec2(1200, 700)))
    {
        if (dialog->IsOk())
        {
            selection.model = dialog->GetFilePathName();

            std::snprintf(m_ModelPath.data(), m_ModelPath.size(), "%s", selection.model->c_str());
            std::cout << "Selected model: " << *selection.model << '\n';
        }

        dialog->Close();
    }

    if (dialog->Display("OpenTextureDialog", ImGuiWindowFlags_NoCollapse, ImVec2(900, 550), ImVec2(1200, 700)))
    {
        if (dialog->IsOk())
        {
            selection.texture = dialog->GetFilePathName();

            std::snprintf(m_TexturePath.data(), m_TexturePath.size(), "%s", selection.texture->c_str());
            std::cout << "Selected texture: " << *selection.texture << '\n';
        }

        dialog->Close();
    }
}

void Editor::DrawTransformSection(Transform &transform)
{
    if (!ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
        return;

    ImGui::DragFloat3("Position", glm::value_ptr(transform.position), 0.1f);
    ImGui::DragFloat3("Rotation", glm::value_ptr(transform.rotation), 0.1f);
    ImGui::DragFloat3("Scale", glm::value_ptr(transform.scale), 0.1f);

    ImGui::Checkbox("Auto Rotate", &transform.shouldAutoRotate);

    if (transform.shouldAutoRotate)
    {
        ImGui::SliderFloat("Rotation Speed", &transform.autoRotateSpeed, 0.0f, 1.0f, "Speed: %.1f");
        ImGui::DragFloat3("Rotation Axis", glm::value_ptr(transform.autoRotateAxis), 0.01f, -1.0f, 1.0f);
    }
}

void Editor::DrawCameraSection(Camera &camera)
{
    if (!ImGui::CollapsingHeader("Camera"))
        return;

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

void Editor::DrawLightingSection(LightingSettings &lighting)
{
    if (!ImGui::CollapsingHeader("Lighting"))
        return;

    ImGui::DragFloat3("Light Direction", glm::value_ptr(lighting.direction), 0.1f);
    ImGui::SliderFloat("Ambient Strength", &lighting.ambientStrength, 0.0f, 1.0f);
    ImGui::SliderFloat("Specular Strength", &lighting.specularStrength, 0.0f, 1.0f);
}

void Editor::DrawMaterialSection(Material &material)
{
    if (!ImGui::CollapsingHeader("Material"))
        return;

    ImGui::ColorEdit3("Base Color", glm::value_ptr(material.baseColor));
    ImGui::ColorEdit3("Ambient", glm::value_ptr(material.ambient), ImGuiColorEditFlags_Float);
    ImGui::ColorEdit3("Diffuse", glm::value_ptr(material.diffuse), ImGuiColorEditFlags_Float);
    ImGui::ColorEdit3("Specular", glm::value_ptr(material.specular), ImGuiColorEditFlags_Float);
    ImGui::SliderFloat("Shininess", &material.shininess, 1.0f, 256.0f);
}