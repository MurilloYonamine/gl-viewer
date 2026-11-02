#include "simulation.h"
#include <vector>
#include <iostream>
#include <iterator>
#include "shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace
{
    constexpr float vertices[] = {
        // X      Y      Z         R     G     B
        -0.5f, -0.5f, -0.5f,     1.0f, 0.0f, 0.0f, // 0
         0.5f, -0.5f, -0.5f,     0.0f, 1.0f, 0.0f, // 1
         0.5f,  0.5f, -0.5f,     0.0f, 0.0f, 1.0f, // 2
        -0.5f,  0.5f, -0.5f,     1.0f, 1.0f, 0.0f, // 3

        -0.5f, -0.5f,  0.5f,     1.0f, 0.0f, 1.0f, // 4
         0.5f, -0.5f,  0.5f,     0.0f, 1.0f, 1.0f, // 5
         0.5f,  0.5f,  0.5f,     1.0f, 1.0f, 1.0f, // 6
        -0.5f,  0.5f,  0.5f,     0.5f, 0.5f, 0.5f  // 7
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
        0, 5, 4
    };
}

Simulation::Simulation() : m_Window(800, 600, "GL Viewer"),
                           m_Vbo(vertices, sizeof(vertices)),
                           m_Ibo(indices,  std::size(indices))
{
    glEnable(GL_DEPTH_TEST);

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

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Bind();
        GLint location = glGetUniformLocation(shader.GetID(), "u_Model");

        float time = static_cast<float>(glfwGetTime());
        glm::mat4 model = glm::mat4(1.0f);

        model = glm::rotate(
            model,
            time,
            glm::vec3(sin(time), time, 0.0f)
        );

        glUniformMatrix4fv(
            location, 
            1, 
            GL_FALSE, 
            glm::value_ptr(model)
        );

        m_Vao.Bind();
        glDrawElements(
            GL_TRIANGLES,
            static_cast<GLsizei>(m_Ibo.GetCount()),
            GL_UNSIGNED_INT,
            nullptr
        );
    

        shader.Unbind();

        m_Window.SwapBuffers();
        m_Window.ProcessEvents();
    }
}