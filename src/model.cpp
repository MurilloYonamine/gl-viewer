#include "model.h"

#include <stdexcept>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

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

    const aiScene *scene = importer.ReadFile(std::string(path), aiProcess_Triangulate);
    std::vector<Mesh> meshes;
    
    if (scene == nullptr)
    {
        throw std::runtime_error(importer.GetErrorString());
    }
    
    meshes.reserve(scene->mNumMeshes);

    for (size_t i = 0; i < scene->mNumMeshes; i++)
    {
        std::vector<float> modelVertices;
        std::vector<unsigned int> modelIndices;

        const aiMesh *mesh = scene->mMeshes[i];
        for (size_t j = 0; j < mesh->mNumVertices; j++)
        {
            const aiVector3D &vertex = mesh->mVertices[j];
            const aiColor4D &color = mesh->mColors[0][j];

            modelVertices.push_back(vertex.x);
            modelVertices.push_back(vertex.y);
            modelVertices.push_back(vertex.z);

            if (mesh->HasVertexColors(0))
            {
                const aiColor4D &color = mesh->mColors[0][j];

                modelVertices.push_back(color.r);
                modelVertices.push_back(color.g);
                modelVertices.push_back(color.b);
            }
            else
            {
                modelVertices.push_back(0.6f);
                modelVertices.push_back(0.6f);
                modelVertices.push_back(0.6f);
            }
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
