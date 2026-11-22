// Created by murillo.gyonamine on 07/09/2026.

#include "app/viewer.h"
#include <glm/glm.hpp>

Viewer::Viewer() : m_Window(1280, 720, "GL Viewer"),
                   m_Editor(m_Window),
                   m_Model("res/models/Duck.gltf"),
                   m_Shader("res/shaders/model.shader"),
                   m_Texture("res/textures/DuckCM.png")
{
}

void Viewer::Update()
{
    double lastFrame = m_Window.GetTime();

    /* Loop until the user closes the window */
    while (m_Window.IsOpen())
    {
        // Window
        m_Window.ProcessEvents();
        m_Window.Update();

        const double currentFrame = m_Window.GetTime();
        const float deltaTime = static_cast<float>(currentFrame - lastFrame);
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
    glm::mat4 model = m_Transform.GetModelMatrix();
    glm::mat4 view = m_Camera.GetView();
    glm::vec3 cameraPos = m_Camera.GetPosition();
    glm::mat4 projection = m_Camera.GetProjection(m_Window.GetAspectRatio());

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_Shader.Bind();
    m_Shader.SetUniform("u_Model", model);
    m_Shader.SetUniform("u_View", view);
    m_Shader.SetUniform("u_Projection", projection);

    m_Shader.SetUniform("u_lightDirection", m_Lighting.direction);
    m_Shader.SetUniform("u_ambientStrength", m_Lighting.ambientStrength);
    m_Shader.SetUniform("u_specularStrength", m_Lighting.specularStrength);
    m_Shader.SetUniform("u_shininess", m_Lighting.shininess);

    m_Shader.SetUniform("u_cameraPos", cameraPos);

    glActiveTexture(GL_TEXTURE0);
    m_Texture.Bind();
    m_Shader.SetUniform("u_Texture", 0);
    
    m_Model.Draw();
    m_Shader.Unbind();
    m_Texture.Unbind();
}
