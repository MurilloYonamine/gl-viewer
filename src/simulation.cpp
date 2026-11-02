#include "simulation.h"
#include <vector>
#include <iostream>
#include <iterator>
#include "shader.h"

namespace
{
    constexpr float vertices[] = {
        -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f
    };

    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3
    };
}

Simulation::Simulation() : m_Window(800, 600, "GL Viewer"),
                           m_Vbo(vertices, sizeof(vertices)),
                           m_Ibo(indices,  std::size(indices))
{
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
}

void Simulation::Update()
{
    Shader shader("res/shaders/basic.shader");

    /* Loop until the user closes the window */
    while (m_Window.IsOpen())
    {
        m_Window.Update();

        glClear(GL_COLOR_BUFFER_BIT);

        shader.Bind();

        m_Vao.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        shader.Unbind();

        m_Window.SwapBuffers();
        m_Window.ProcessEvents();
    }
}