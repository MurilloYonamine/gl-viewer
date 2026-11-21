#include "simulation.h"
#include "shader.h"

#include <iostream>

#include <iterator>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>

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
    const GLint shaderModel = glGetUniformLocation(shader.GetID(), "u_Model");
    const GLint shaderView = glGetUniformLocation(shader.GetID(), "u_View");
    const GLint shaderProjection = glGetUniformLocation(shader.GetID(), "u_Projection");

    float lastFrame = static_cast<float>(glfwGetTime());
    float deltaTime = 0.0f;
    float rotationAngle = 0.0f;

    float aspect = 800.0f / 600.0f;
    float rotation = 1.0f;

    Assimp::Importer importer;

    const aiScene *scene = importer.ReadFile(
        "res/models/triangle.obj",
        aiProcess_Triangulate);

    std::vector<float> modelVertices;
    std::vector<unsigned int> modelIndices;

    if (scene != nullptr)
    {
        std::cout << "Loading the model..." << std::endl;
        const aiMesh *mesh = scene->mMeshes[0];

        std::cout << "Vertices: " << mesh->mNumVertices << std::endl;
        std::cout << "Faces: " << mesh->mNumFaces << std::endl;

        for (size_t i = 0; i < mesh->mNumVertices; i++)
        {
            std::cout << "Vertex " << i << ": ";

            const aiVector3D &vertex = mesh->mVertices[i];

            std::cout << vertex.x << ", "
                      << vertex.y << ", "
                      << vertex.z << "\n";

            modelVertices.push_back(vertex.x);
            modelVertices.push_back(vertex.y);
            modelVertices.push_back(vertex.z);
            modelVertices.push_back(1.0f); // R
            modelVertices.push_back(1.0f); // G
            modelVertices.push_back(1.0f); // B
        }
        for (size_t i = 0; i < mesh->mNumFaces; i++)
        {
            const aiFace &face = mesh->mFaces[i];

            std::cout << "Face " << i << ": ";
            for (size_t j = 0; j < face.mNumIndices; j++)
            {
                std::cout << face.mIndices[j] << " ";
                modelIndices.push_back(face.mIndices[j]);
            }
            std::cout << '\n';
        }

        std::cout << "Floats: " << modelVertices.size() << '\n';
        std::cout << "Indices: " << modelIndices.size() << '\n';
    }
    else
    {
        std::cout << importer.GetErrorString() << std::endl;
    }

    VertexArray modelVao;
    VertexBuffer modelVbo(modelVertices.data(), modelVertices.size() * sizeof(float));
    IndexBuffer modelIbo(modelIndices.data(), modelIndices.size());

    VertexBufferLayout modelLayout;

    modelLayout.PushFloat(3); // Position
    modelLayout.PushFloat(3); // Color

    modelVao.AddBuffer(modelVbo, modelLayout);
    modelVao.Unbind();

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

        // m_Vao.Bind();
        // glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_Ibo.GetCount()), GL_UNSIGNED_INT, nullptr);

        modelVao.Bind();
        glDrawElements(
            GL_TRIANGLES,
            static_cast<GLsizei>(modelIbo.GetCount()),
            GL_UNSIGNED_INT,
            nullptr);

        shader.Unbind();

        // Render Imgui
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        m_Window.SwapBuffers();
    }
}
