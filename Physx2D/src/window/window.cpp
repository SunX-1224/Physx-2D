#include "pch.h"
#include "window.h"

namespace Physx2D {
    WindowProps Window::properties = WindowProps();

    Window::Window(WindowProps props, uint32_t version_major, uint32_t version_minor) {
        properties = props;
        VERSION_MAJOR = version_major;
        VERSION_MINOR = version_minor;

        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, VERSION_MAJOR);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, VERSION_MINOR);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

        #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        #endif

        glfwWindowHint(GLFW_RESIZABLE, true);

        m_window = glfwCreateWindow(properties.WIDTH, properties.HEIGHT, properties.TITLE, NULL, NULL);
        glfwMakeContextCurrent(m_window);
        
        PHSX2D_ASSERT( gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to initialize glad%s", "\n");

        glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
                glfwSetWindowSize(window, width, height);
                glViewport(0, 0, width, height);
                properties.WIDTH = width;
                properties.HEIGHT = height;
            }
        );

        glfwSwapInterval(0);        
    }

    void Window::OnInit() {
        glfwGetWindowSize(m_window, &properties.WIDTH, &properties.HEIGHT);
        glViewport(0, 0, properties.WIDTH, properties.HEIGHT);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    inline void Window::SetVsync(bool value) {
        glfwSwapInterval(value);
    }

    inline bool Window::ShouldClose() {
        return glfwWindowShouldClose(m_window);
    }

    inline void Window::SetClose(bool value){
        glfwSetWindowShouldClose(m_window, value);
    }

    inline ivec2 Window::GetResolution() const {
        return ivec2(properties.WIDTH, properties.HEIGHT);
    }

    inline int Window::GetWidth() const {
        return properties.WIDTH;
    }

    inline int Window::GetHeight() const {
        return properties.HEIGHT;
    }

    inline void Window::FillScreen(Color color) {
        glClearColor(color.x, color.y, color.z, color.w);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    inline void Window::SetTitle(const char* title){
        glfwSetWindowTitle(m_window, properties.TITLE = title);
    }

    inline void Window::OnUpdate() {
        glfwPollEvents();
        glfwSwapBuffers(m_window);
    }

    Window::~Window() {
        glfwDestroyWindow(m_window);
    }
}