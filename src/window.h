//
// Created by murillo.gyonamine on 08/08/2026.
//

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

    private:
        GLFWwindow* m_Window;
};
