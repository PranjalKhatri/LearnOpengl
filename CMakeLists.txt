cmake_minimum_required(VERSION 3.27.8)
project(OpenGLTest LANGUAGES CXX)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source file
add_executable(OpenGLTest main.cpp)

# Include directory for GLFW headers
target_include_directories(OpenGLTest PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Link library directory
target_link_directories(OpenGLTest PRIVATE ${CMAKE_SOURCE_DIR}/lib)

# Windows system libs + GLFW + OpenGL
target_link_libraries(OpenGLTest PRIVATE
    glfw3
    opengl32
    gdi32
    user32
)