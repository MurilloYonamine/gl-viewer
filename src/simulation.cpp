#include "simulation.h"
#include <vector>
#include <iostream>
#include "shader.h"

unsigned int VAO;
unsigned int VBO;
unsigned int EBO;

Simulation::Simulation() : m_Window(800, 600, "GL Viewer")
{
    float vertices[] = {
        // posição          // cor
        -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // 0
         0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // 1
         0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // 2
        -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f  // 3
    };

    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // cleaning
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); 
    
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

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        shader.Unbind();

        m_Window.SwapBuffers();
        m_Window.ProcessEvents();
    }
}