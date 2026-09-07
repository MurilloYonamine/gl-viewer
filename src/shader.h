#pragma once

#include <string>
#include "gl/glew.h"

class Shader {
    public:
        Shader(const std::string& filepath);
        void Bind();
        void Unbind();

    private:
        GLuint m_RendererID;
        GLuint CompileShader(GLenum type, const char* source);
        GLuint CreateShaderProgram(GLuint vertexShader, GLuint fragmentShader);
};