#pragma once

#include "gl/glew.h"
#include <string>

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

    private:
        GLuint m_RendererID;
        GLuint CompileShader(GLenum type, const char *source);
        GLuint CreateShaderProgram(GLuint vertexShader, GLuint fragmentShader);
};
