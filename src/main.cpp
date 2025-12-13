#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "gl_types.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "vertex_buffers.hpp"
#include "stb_image.h"

#include <iostream>

using namespace pop::gfx;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH  = 800;
const unsigned int SCR_HEIGHT = 600;

int main() {
    // init
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    // register callback for resizing
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    float vertices[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 0.0f,
        0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f, 0.5f,  0.5f,  0.0f, 1.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f,

        -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
        0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f,  -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 1.0f,
        0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

        -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, 0.5f,  0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f};
    unsigned int indices[] = {
        0, 1, 3,  // first triangle
        1, 2, 3   // second triangle
    };

    Shader vertexShader{ShaderType::Vertex};
    Shader fragmentShader{ShaderType::Fragment};
    if (!pop::gfx::Shader::LoadAndCompile(vertexShader, "shaders/vertex.glsl"))
        return 1;
    if (!pop::gfx::Shader::LoadAndCompile(fragmentShader,
                                          "shaders/fragment.glsl"))
        return 1;
    ShaderProgram shaderProgram{};
    shaderProgram.Attach(vertexShader);
    shaderProgram.Attach(fragmentShader);
    if (!shaderProgram.Link()) {
        std::cerr << shaderProgram.GetError() << "\n";
        return 1;
    }

    VertexArray VAO{};
    VAO.Bind();
    // 2. copy our vertices array in a buffer for OpenGL to use
    GLBuffer VBO{BufferType::kArrayBuffer};
    // EBO{BufferType::kElementArrayBuffer};
    VBO.BufferData(sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 3. then set our vertex attributes pointers
    VAO.AddAttribute({0, 3, GLType::kFloat, false, 5 * sizeof(float), 0});
    // EBO.Bind();
    // EBO.BufferData(sizeof(indices), indices, GL_STATIC_DRAW);

    Texture texwood{TextureType::kTexture2D};
    Texture texface{TextureType::kTexture2D};
    texwood.LoadFromFile("textures/wood.jpg", true);
    texface.LoadFromFile("textures/face.png", true);
    VAO.AddAttribute(
        {1, 2, GLType::kFloat, false, 5 * sizeof(float), 3 * sizeof(float)});
    shaderProgram.use();
    shaderProgram.SetUniformInt("tex1", 0);
    shaderProgram.SetUniformInt("tex2", 1);
    // rendering loop
    while (!glfwWindowShouldClose(window)) {
        // input
        processInput(window);
        // rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        texwood.Bind(0);
        texface.Bind(1);
        shaderProgram.use();
        // create transformations
        glm::mat4 model = glm::mat4(
            1.0f);  // make sure to initialize matrix to identity matrix first
        glm::mat4 view       = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        model                = glm::rotate(model, (float)glfwGetTime(),
                                           glm::vec3(0.5f, 1.0f, 0.0f));
        view       = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        projection = glm::perspective(glm::radians(45.0f),
                                      (float)SCR_WIDTH / (float)SCR_HEIGHT,
                                      0.1f, 100.0f);
        shaderProgram.SetUniformMat4("model", glm::value_ptr(model), false);
        shaderProgram.SetUniformMat4("view", glm::value_ptr(view), false);
        shaderProgram.SetUniformMat4("projection", glm::value_ptr(projection),
                                     false);
        VAO.Bind();
        glDrawArrays(GL_TRIANGLES, 0, 36);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // cleanup resources and terminate
    glfwTerminate();
    return 0;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
