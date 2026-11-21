#include "shader.h"

#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/gtc/type_ptr.hpp>


Shader::Shader(const std::string &filepath)
{
    std::ifstream stream(filepath);
    if (!stream.is_open())
    {
        throw std::runtime_error("Failed to open shader file: " + filepath);
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

    GLuint vertexShader = 0;
    GLuint fragmentShader = 0;

    try
    {
        vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSource.c_str());
        fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSource.c_str());
        m_RendererID = CreateShaderProgram(vertexShader, fragmentShader);
    }
    catch (...)
    {
        if (vertexShader != 0)
            glDeleteShader(vertexShader);

        if (fragmentShader != 0)
            glDeleteShader(fragmentShader);

        throw;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
    glDeleteProgram(m_RendererID);
}

Shader &Shader::operator=(Shader &&other) noexcept
{
    if (this != &other)
    {
        glDeleteProgram(m_RendererID);
        m_RendererID = other.m_RendererID;
        other.m_RendererID = 0;
    }

    return *this;
}

Shader::Shader(Shader &&other) noexcept : m_RendererID(other.m_RendererID)
{
    other.m_RendererID = 0;
}

void Shader::Bind()
{
    glUseProgram(m_RendererID);
}

void Shader::Unbind()
{
    glUseProgram(0);
}

GLint Shader::GetUniformLocation(const std::string &name) const
{
    GLint location = glGetUniformLocation(m_RendererID, name.c_str());
    return location;
}

void Shader::SetUniform(const std::string &name, float value)
{
    Bind();
    GLint location = GetUniformLocation(name);
    glUniform1f(location, value);
}

void Shader::SetUniform(const std::string &name, const glm::vec3 &value)
{
    Bind();
    GLint location = GetUniformLocation(name);
    glUniform3f(location, value.x, value.y, value.z);
}

void Shader::SetUniform(const std::string &name, const glm::mat4 &value)
{
    Bind();
    GLint location = GetUniformLocation(name);
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

GLuint Shader::CompileShader(GLenum type, const char *source)
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

        throw std::runtime_error(std::string("Shader compilation failed: ") + message);
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
    if (success != GL_TRUE)
    {
        GLsizei logLength;
        GLchar message[1024];
        glGetProgramInfoLog(shaderProgram, 1024, &logLength, message);

        throw std::runtime_error(std::string("Shader program linking failed: ") + message);
    }

    return shaderProgram;
}