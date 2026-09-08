#include "shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const std::string &filepath)
{
    std::ifstream stream(filepath);
    if (!stream.is_open())
    {
        std::cout << "ERROR: Could not open shader file: " << filepath << std::endl;
    }

    std::stringstream buffer;
    buffer << stream.rdbuf();

    std::string source = buffer.str();

    size_t vertexPosition = source.find("#shader vertex");
    size_t fragmentPosition = source.find("#shader fragment");

    size_t vertexStart = vertexPosition + std::string("#shader vertex").size();
    size_t fragmentStart = fragmentPosition + std::string("#shader fragment").size();

    std::string vertexSource = source.substr(vertexStart, fragmentPosition - vertexStart);
    std::string fragmentSource = source.substr(fragmentStart);

    GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSource.c_str());
    GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSource.c_str());

    m_RendererID = CreateShaderProgram(vertexShader, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
    glDeleteProgram(m_RendererID);
}

void Shader::Bind()
{
    glUseProgram(m_RendererID);
}

void Shader::Unbind()
{
    glUseProgram(0);
}

GLuint Shader::CompileShader(GLenum type, const char* source)
{
    GLuint shader = glCreateShader(type); // ID
    glShaderSource(shader, 1, &source, nullptr);

    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (success != GL_TRUE)
    {
        GLsizei logLength;
        GLchar message[1024];

        glGetShaderInfoLog(shader, 1024, &logLength, message);

        std::cout << "ERROR: Shader compilation failed\n";
        std::cout << message << std::endl;
    }

    return shader;
}

GLuint Shader::CreateShaderProgram(GLuint vertexShader, GLuint fragmentShader) 
{
    GLuint shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);

    GLint success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(success != GL_TRUE) {
        GLsizei logLength;
        GLchar message[1024];
        glGetProgramInfoLog(shaderProgram, 1024, &logLength, message);

        std::cout << "ERROR: Creating Shader Program failed\n";
        std::cout << message << std::endl;
    }

    return shaderProgram;
}