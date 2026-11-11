#include "simulation.h"
#include "shader.h"

#include <vector>
#include <iostream>
#include <iterator>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

namespace
{
    constexpr float vertices[] = {
        // X      Y      Z         R     G     B
        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, // 0
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  // 1
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f,   // 2
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f,  // 3

        -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 1.0f, // 4
        0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 1.0f,  // 5
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f,   // 6
        -0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f   // 7
    };

    constexpr unsigned int indices[] = {
        // front (+Z)
        4, 5, 6,
        4, 6, 7,

        // back (-Z)
        1, 0, 3,
        1, 3, 2,

        // left (-X)
        0, 4, 7,
        0, 7, 3,

        // right (+X)
        5, 1, 2,
        5, 2, 6,

        // top (+Y)
        3, 7, 6,
        3, 6, 2,

        // bottom (-Y)
        0, 1, 5,
        0, 5, 4};
}

Simulation::Simulation() : m_Window(800, 600, "GL Viewer"),
                           m_Vbo(vertices, sizeof(vertices)),
                           m_Ibo(indices, std::size(indices))
{
    glEnable(GL_DEPTH_TEST);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(m_Window.GetNativeWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 460");

    m_Vao.Bind();
    m_Ibo.Bind();
    m_Vbo.Bind();

    m_Layout.PushFloat(3); // position
    m_Layout.PushFloat(3); // color

    m_Vao.AddBuffer(m_Vbo, m_Layout);

    // cleaning
    m_Vbo.Unbind();
    m_Vao.Unbind();
}

Simulation::~Simulation()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Simulation::Update()
{
    Shader shader("res/shaders/basic.shader");
    GLint shaderModel = glGetUniformLocation(shader.GetID(), "u_Model");
    GLint shaderView = glGetUniformLocation(shader.GetID(), "u_View");
    GLint shaderProjection = glGetUniformLocation(shader.GetID(), "u_Projection");

    float fov = 100.0f;

    glm::mat4 view = glm::lookAt(
        glm::vec3(0.0f, 0.0f, 3.0f), // camera position
        glm::vec3(0.0f, 0.0f, 0.0f), // point to be observed
        glm::vec3(0.0f, 1.0f, 0.0f)  // direction up
    );

    float aspect = 800.0f / 600.0f;
    float rotation = 0;

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

        ImGui::Begin("GL Viewer");
        ImGui::SliderFloat("Field of View", &fov, 20.0f, 100.0f);
        ImGui::SliderFloat("Rotation", &rotation, 0.0f, 25.0f);
        ImGui::End();

        // Transformation
        float time = static_cast<float>(glfwGetTime());
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, rotation * time, glm::vec3(sin(time), time, 0.0f));
        glm::mat4 projection = glm::perspective(glm::radians(fov), aspect, 0.1f, 100.0f);

        // Scene
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Bind();

        glUniformMatrix4fv(shaderModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(shaderView, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(shaderProjection, 1, GL_FALSE, glm::value_ptr(projection));

        m_Vao.Bind();
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_Ibo.GetCount()), GL_UNSIGNED_INT, nullptr);

        shader.Unbind();

        // Render Imgui
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        m_Window.SwapBuffers();
    }
}