// Created by murillo.gyonamine on 09/08/2026.

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

class Window
{
public:
    Window(int width = 800, int height = 600, std::string_view title = "OpenGL Window");
    ~Window();
    void Update() const;
    void SwapBuffers() const;
    void ProcessEvents() const;
    bool IsOpen() const;
    GLFWwindow *GetNativeWindow() const { return m_Window; }
    float GetAspectRatio() const;
    float GetTime() const { return glfwGetTime(); }

private:
    GLFWwindow *m_Window;

    void InitializeGLFW(int width, int height, std::string_view title);
    void InitializeOpenGL();
    void ConfigureViewport();
    void ConfigureDebugOutput();
};
