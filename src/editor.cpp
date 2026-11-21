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

void Editor::OnGUI(Camera &camera, glm::vec3 &lightDirection, float &ambientStrength, float& specularStrength)
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
        ImGui::SliderFloat("Specular Strength", &specularStrength, 0.0f, 1.0f);
    }

    ImGui::End();
}