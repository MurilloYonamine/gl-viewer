// Created by murillo.gyonamine on 14/11/2026.

#pragma once

#include "scene/camera.h"
#include "core/window.h"
#include "scene/lighting_settings.h"
#include "scene/transform.h"
#include "../rendering/material.h"
#include <optional>
#include <array>

struct FileSelection
{
    std::optional<std::string> model;
    std::optional<std::string> texture;
    std::optional<std::string> specularMap;
};

class Editor
{
    public:
        Editor(Window &window);
        ~Editor();

        void BeginFrame();
        void EndFrame();
        FileSelection OnGUI(Camera &camera, LightingSettings &lighting, Transform &transform, Material &material);

    private:
        Window &m_Window;
        std::array<char, 512> m_ModelPath{};
        std::array<char, 512> m_TexturePath{};
        std::array<char, 512> m_SpecularMapPath{};

        void DrawModelSection();
        void HandleFileDialogs(FileSelection &selection);

        void DrawTransformSection(Transform &transform);
        void DrawCameraSection(Camera &camera);
        void DrawLightingSection(LightingSettings &lighting);
        void DrawMaterialSection(Material &material);
};
