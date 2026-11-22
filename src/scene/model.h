// Created by murillo.gyonamine on 21/11/2026.

#pragma once

#include "rendering/mesh.h"
#include <string_view>

class Model
{   
    public:
        Model(std::string_view path);

        void Draw();

    private:
        std::vector<Mesh> m_Meshes;
        std::vector<Mesh> LoadMeshes(std::string_view path);
};
