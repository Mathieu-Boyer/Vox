#pragma once

#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl3.h>
#include "GLFW/glfw3.h"
#include <string>

class GLApp
{
private:
    GLFWwindow *window;
    void init();

public:
    GLApp(const int width, const int height,  const std::string &name);
    ~GLApp();
    void render();
};

GLApp::GLApp(const int width, const int height,  const std::string &name)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);

    if (!window)
        throw std::runtime_error("Window couldn't be oppened.");

    glfwMakeContextCurrent(window);
}


void GLApp::render()
{
    while (!glfwWindowShouldClose(window)){
        glfwPollEvents();
        glClearColor(.2, .4, .6, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
    }
}

GLApp::~GLApp()
{
    if (window != nullptr)
        glfwDestroyWindow(window);
    glfwTerminate();
}
