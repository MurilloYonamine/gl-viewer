// Created by murillo.gyonamine on 09/08/2026.

#include "core/window.h"
#include "rendering/gl_debug.h"
#include <stdexcept>

Window::Window(const int width, const int height, const std::string_view title)
{
    InitializeGLFW(width, height, title);
    InitializeOpenGL();
    ConfigureViewport();
    ConfigureDebugOutput();

    glEnable(GL_DEPTH_TEST);

    std::cout << "OpenGL: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
}

Window::~Window()
{
    if (m_Window)
    {
        glfwDestroyWindow(m_Window);
        m_Window = nullptr;
    }

    glfwTerminate();
}

void Window::Update() const
{
    /* Process input */
    if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(m_Window, true);
    }
}

/* Swap front and back buffers */
void Window::SwapBuffers() const
{
    glfwSwapBuffers(m_Window);
}

/* Poll for and process events */
void Window::ProcessEvents() const
{
    glfwPollEvents();
}

bool Window::IsOpen() const
{
    return !glfwWindowShouldClose(m_Window);
}

float Window::GetAspectRatio() const
{
    int width, height;

    glfwGetFramebufferSize(m_Window, &width, &height);

    if (height == 0 || width == 0)
    {
        return 1.0f;
    }

    return static_cast<float>(width) / height;
}

void Window::InitializeGLFW(int width, int height, std::string_view title)
{
    /* Initialize the glfw */
    if (!glfwInit())
    {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    m_Window = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);
    if (!m_Window)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(m_Window);
}

void Window::InitializeOpenGL()
{
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        glfwDestroyWindow(m_Window);
        glfwTerminate();

        throw std::runtime_error("Failed to initialize GLEW");
    }
}

void Window::ConfigureViewport()
{
    int framebufferWidth, framebufferHeight;
    glfwGetFramebufferSize(m_Window, &framebufferWidth, &framebufferHeight);

    glViewport(0, 0, framebufferWidth, framebufferHeight);

    glfwSetFramebufferSizeCallback(
        m_Window,
        [](GLFWwindow *window, int width, int height)
        {
            glViewport(0, 0, width, height);
        });
}

void Window::ConfigureDebugOutput()
{
    int flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);

    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
    {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

        glDebugMessageCallback(glDebugOutput, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    }
}
