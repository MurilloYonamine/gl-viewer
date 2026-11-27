// Created by murillo.gyonamine on 07/09/2026.

#include "app/viewer.h"
#include <glm/glm.hpp>
#include <iostream>

Viewer::Viewer() : m_Window(1280, 720, "GL Viewer"),
                   m_Editor(m_Window),
                   m_Shader("res/shaders/model.shader")
{
    // m_Texture.emplace(nullptr);
    // m_Material.texture = &m_Texture.value();
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
        auto selection = m_Editor.OnGUI(m_Camera, m_Lighting, m_Transform, m_Material);

        if (selection.model)
        {
            try
            {
                m_Model = Model(*selection.model);
            }
            catch (const std::exception &e)
            {
                std::cerr << "Failed to load model: " << e.what() << '\n';
            }
        }

        if (selection.texture)
        {
            m_Material.texture = nullptr;

            try
            {
                m_Texture.emplace(*selection.texture);
                m_Material.texture = &m_Texture.value();
            }
            catch (const std::exception &e)
            {
                std::cerr << "Failed to load texture: " << e.what() << '\n';
            }
        }

        if (selection.specularMap)
        {
            m_Material.specularMap = nullptr;

            try
            {
                m_SpecularTexture.emplace(*selection.specularMap);
                m_Material.specularMap = &m_SpecularTexture.value();
            }
            catch (const std::exception &e)
            {
                std::cerr << "Failed to load specular texture: " << e.what() << '\n';
            }
        }

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

    m_Shader.SetUniform("u_LightDirection", m_Lighting.direction);
    m_Shader.SetUniform("u_AmbientStrength", m_Lighting.ambientStrength);
    m_Shader.SetUniform("u_SpecularStrength", m_Lighting.specularStrength);
    m_Shader.SetUniform("u_ShininessStrength", m_Lighting.shininessStrength);

    m_Shader.SetUniform("u_Material.baseColor", m_Material.baseColor);
    m_Shader.SetUniform("u_Material.ambient", m_Material.ambient);
    m_Shader.SetUniform("u_Material.shininess", m_Material.shininess);
    m_Shader.SetUniform("u_Material.diffuse", m_Material.diffuse);
    m_Shader.SetUniform("u_Material.specular", m_Material.specular);

    m_Shader.SetUniform("u_CameraPos", cameraPos);

    bool hasTexture = m_Material.texture != nullptr;
    m_Shader.SetUniform("u_HasTexture", static_cast<int>(hasTexture));

    bool hasSpecularMap = static_cast<int>(m_Material.specularMap != nullptr);
    m_Shader.SetUniform("u_HasSpecularMap", hasSpecularMap);

    if (hasSpecularMap)
    {
        glActiveTexture(GL_TEXTURE1);
        m_Material.specularMap->Bind();
        m_Shader.SetUniform("u_SpecularMap", 1);
    }

    if (hasTexture)
    {
        glActiveTexture(GL_TEXTURE0);
        m_Material.texture->Bind();
        m_Shader.SetUniform("u_Texture", 0);
    }

    if (m_Model)
    {
        m_Model->Draw();
    }

    m_Shader.Unbind();
    if (m_Material.texture)
    {
        glActiveTexture(GL_TEXTURE0);
        m_Material.texture->Bind();
    }

    if (m_Material.specularMap)
    {
        glActiveTexture(GL_TEXTURE1);
        m_Material.specularMap->Bind();
    }
}
