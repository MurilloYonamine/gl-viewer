// Created by murillo.gyonamine on 07/09/2026.

#pragma once

#include <string>
#include <GL/glew.h>

#include <glm/glm.hpp>


class Shader
{
    public:
        Shader(const std::string &filepath);
        ~Shader();
        Shader(const Shader &) = delete;
        Shader &operator=(Shader &&other) noexcept;
        Shader(Shader &&other) noexcept;

        void Bind();
        void Unbind();

        GLuint GetID() const { return m_RendererID; }
        GLint GetUniformLocation(const std::string& name) const;

        void SetUniform(const std::string &name, int value);
        void SetUniform(const std::string &name, float value);
        void SetUniform(const std::string &name, const glm::vec3 &value);
        void SetUniform(const std::string &name, const glm::vec4 &value);
        void SetUniform(const std::string &name, const glm::mat4 &value);

    private:
        GLuint m_RendererID;
        GLuint CompileShader(GLenum type, const char *source);
        GLuint CreateShaderProgram(GLuint vertexShader, GLuint fragmentShader);
};
