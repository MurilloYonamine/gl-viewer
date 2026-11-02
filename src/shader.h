#pragma once

#include <string>
#include "gl/glew.h"

class Shader {
    public:
        Shader(const std::string& filepath);
        ~Shader();
        void Bind();
        void Unbind();
        GLuint GetID() const { return m_RendererID; }

    private:
        GLuint m_RendererID;
        GLuint CompileShader(GLenum type, const char* source);
        GLuint CreateShaderProgram(GLuint vertexShader, GLuint fragmentShader);
};