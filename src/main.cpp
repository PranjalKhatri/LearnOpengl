#include <GLFW/glfw3.h>
#include <iostream>

int main() {
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(640, 480, "Version", NULL, NULL);
    glfwMakeContextCurrent(window);

    std::cout << "OpenGL Version  : " << glGetString(GL_VERSION)  << "\n";
    std::cout << "Renderer        : " << glGetString(GL_RENDERER) << "\n";
    std::cout << "Vendor          : " << glGetString(GL_VENDOR)   << "\n";

    glfwTerminate();
}
