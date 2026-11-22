// Created by murillo.gyonamine on 21/11/2026.

#include "scene/model.h"

#include <stdexcept>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "rendering/vertex.h"

Model::Model(std::string_view path)
{
    m_Meshes = LoadMeshes(path);
}

void Model::Draw()
{
    for (size_t i = 0; i < m_Meshes.size(); i++)
    {
        m_Meshes[i].Draw();
    }
}

std::vector<Mesh> Model::LoadMeshes(std::string_view path)
{
    Assimp::Importer importer;

    const aiScene *scene = importer.ReadFile(std::string(path), aiProcess_Triangulate | aiProcess_GenSmoothNormals);
    std::vector<Mesh> meshes;

    if (scene == nullptr)
    {
        throw std::runtime_error(importer.GetErrorString());
    }

    meshes.reserve(scene->mNumMeshes);

    for (size_t i = 0; i < scene->mNumMeshes; i++)
    {
        std::vector<Vertex> modelVertices;
        std::vector<unsigned int> modelIndices;

        const aiMesh *mesh = scene->mMeshes[i];
        for (size_t j = 0; j < mesh->mNumVertices; j++)
        {
            Vertex vertex{};

            const aiVector3D &position = mesh->mVertices[j];

            vertex.position = {position.x, position.y, position.z};

            if (mesh->HasVertexColors(0))
            {
                const aiColor4D &color = mesh->mColors[0][j];
                vertex.color = {color.r, color.g, color.b};
            }
            else
            {
                vertex.color = {0.6f, 0.6f, 0.6f};
            }

            if (mesh->HasTextureCoords(0))
            {
                const aiVector3D &texCoords = mesh->mTextureCoords[0][j];
                vertex.texCoords = {texCoords.x, texCoords.y};
            }
            else
            {
                vertex.texCoords = {0.0f, 0.0f};
            }

            const aiVector3D &normal = mesh->mNormals[j];
            vertex.normal = {normal.x, normal.y, normal.z};

            modelVertices.push_back(vertex);
        }

        for (size_t j = 0; j < mesh->mNumFaces; j++)
        {
            const aiFace &face = mesh->mFaces[j];
            for (size_t k = 0; k < face.mNumIndices; k++)
            {
                modelIndices.push_back(face.mIndices[k]);
            }
        }

        meshes.emplace_back(modelVertices, modelIndices);
    }

    return meshes;
}
