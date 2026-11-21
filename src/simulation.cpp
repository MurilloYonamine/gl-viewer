#include "simulation.h"
#include "shader.h"
#include "mesh.h"

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>

Simulation::Simulation() : m_Window(800, 600, "GL Viewer"),
                           m_Mesh(LoadMesh("res/models/triangle.obj"))
{
    glEnable(GL_DEPTH_TEST);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(m_Window.GetNativeWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 460");
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

        m_Mesh.Draw();

        shader.Unbind();

        // Render Imgui
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        m_Window.SwapBuffers();
    }
}

Mesh Simulation::LoadMesh(std::string_view path)
{
    Assimp::Importer importer;

    const aiScene *scene = importer.ReadFile(path.data(), aiProcess_Triangulate);
    std::vector<float> modelVertices;
    std::vector<unsigned int> modelIndices;

    if (scene != nullptr)
    {
        const aiMesh *mesh = scene->mMeshes[0];
        for (size_t i = 0; i < mesh->mNumVertices; i++)
        {
            const aiVector3D &vertex = mesh->mVertices[i];

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
            for (size_t j = 0; j < face.mNumIndices; j++)
            {
                modelIndices.push_back(face.mIndices[j]);
            }
        }
    }
    else
    {
        throw std::runtime_error(importer.GetErrorString());
    }
    return Mesh(modelVertices, modelIndices);
}
