#include "viewer.h"
#include "shader.h"
#include "mesh.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>

Viewer::Viewer() : m_Window(800, 600, "GL Viewer"),
                   m_Model("res/models/monkey.obj")
{
    glEnable(GL_DEPTH_TEST);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(m_Window.GetNativeWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 460");
}

Viewer::~Viewer()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Viewer::Update()
{
    Shader shader("res/shaders/model.shader");
    const GLint shaderModel = glGetUniformLocation(shader.GetID(), "u_Model");
    const GLint shaderView = glGetUniformLocation(shader.GetID(), "u_View");
    const GLint shaderProjection = glGetUniformLocation(shader.GetID(), "u_Projection");

    float lastFrame = static_cast<float>(glfwGetTime());
    float deltaTime = 0.0f;
    float rotationAngle = 0.0f;

    float aspect = 800.0f / 600.0f;
    float rotation = 1.0f;

    /* Loop until the user closes the window */
    while (m_Window.IsOpen())
    {
        // Window
        m_Window.ProcessEvents();
        m_Window.Update();

        // Imgui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        m_Editor.OnGUI(m_Camera);

        // Transformation
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        rotationAngle += rotation * deltaTime;

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = m_Camera.GetView();
        glm::mat4 projection = m_Camera.GetProjection(aspect);

        // Scene
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Bind();

        glUniformMatrix4fv(shaderModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(shaderView, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(shaderProjection, 1, GL_FALSE, glm::value_ptr(projection));

        m_Model.Draw();

        shader.Unbind();

        // Render Imgui
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        m_Window.SwapBuffers();
    }
}