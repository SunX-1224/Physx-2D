#include "window.h"

namespace Physx2D {

    Window::Window(WindowProps props, uint32_t version_major, uint32_t version_minor) {
        properties = props;
        VERSION_MAJOR = version_major;
        VERSION_MINOR = version_minor;
        m_window = NULL;
    }

    void Window::Init() {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, VERSION_MAJOR);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, VERSION_MINOR);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
        glfwWindowHint(GLFW_RESIZABLE, properties.RESIZABLE);

        m_window = glfwCreateWindow(properties.WIDTH, properties.HEIGHT, properties.TITLE, properties.FULLSCREEN_MODE ? glfwGetPrimaryMonitor() : NULL, NULL);
        glfwMakeContextCurrent(m_window);

        glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
            glfwSetWindowSize(window, width, height);
            glViewport(0, 0, width, height);
            });

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cout << "Failed to initialize GLAD" << std::endl;
        }

        glViewport(0, 0, properties.WIDTH, properties.HEIGHT);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    bool Window::ShouldClose() {
        return glfwWindowShouldClose(m_window);
    }

    void Window::SetClose(bool value){
        glfwSetWindowShouldClose(m_window, value);
    }

    vec2 Window::GetResolution() {
        glfwGetWindowSize(m_window, (int*)&properties.WIDTH, (int*)&properties.HEIGHT);
        return vec2(properties.WIDTH, properties.HEIGHT);
    }

    void Window::FillScreen(Color color) {
        glClearColor(color.x, color.y, color.z, color.w);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Window::SetTitle(const char* title){
        properties.TITLE = title;
        glfwSetWindowTitle(m_window, title);
    }

    void Window::UpdateEvents() {
        glfwPollEvents();
    }

    void Window::Update() {
        glfwSwapBuffers(m_window);
    }

    void Window::Destroy() {
        glfwDestroyWindow(m_window);
    }

}