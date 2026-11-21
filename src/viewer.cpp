#include "viewer.h"
#include "shader.h"
#include "mesh.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Viewer::Viewer() : m_Window(800, 600, "GL Viewer"),
                   m_Editor(m_Window),
                   m_Model("res/models/monkey.obj"),
                   m_Shader("res/shaders/model.shader") {}

void Viewer::Update()
{
    float lastFrame = static_cast<float>(glfwGetTime());

    /* Loop until the user closes the window */
    while (m_Window.IsOpen())
    {
        // Window
        m_Window.ProcessEvents();
        m_Window.Update();

        const float currentFrame = static_cast<float>(glfwGetTime());
        const float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        m_Transform.Update(deltaTime);

        m_Editor.BeginFrame();
        m_Editor.OnGUI(m_Camera, m_Lighting, m_Transform);

        RenderScene();

        m_Editor.EndFrame();
        m_Window.SwapBuffers();
    }
}

void Viewer::RenderScene()
{
    glm::mat4 model = m_Transform.GetMatrix();
    glm::mat4 view = m_Camera.GetView();
    glm::vec3 cameraPos = m_Camera.GetPosition();
    glm::mat4 projection = m_Camera.GetProjection(m_Window.GetAspectRatio());

    // Scene
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_Shader.Bind();
    m_Shader.SetUniform("u_Model", model);
    m_Shader.SetUniform("u_View", view);
    m_Shader.SetUniform("u_Projection", projection);

    m_Shader.SetUniform("u_lightDirection", m_Lighting.direction);
    m_Shader.SetUniform("u_ambientStrength", m_Lighting.ambientStrength);
    m_Shader.SetUniform("u_specularStrength", m_Lighting.specularStrength);

    m_Shader.SetUniform("u_cameraPos", cameraPos);
    m_Model.Draw();
    m_Shader.Unbind();
}