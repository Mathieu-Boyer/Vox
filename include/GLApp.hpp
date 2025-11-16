#pragma once

#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl3.h>
#include "GLFW/glfw3.h"
#include <string>

class GLApp
{
private:
    int _width;
    int _height;
    const std::string &_name;
    GLFWwindow *_window;
    void init();



public:
    GLApp(const int width, const int height,  const std::string &name);
    ~GLApp();
    void render();
};

GLApp::GLApp(const int width, const int height,  const std::string &name) : _width(width),_height(height),_name(name)
{

    init();


}


void GLApp::init(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    _window = glfwCreateWindow(_width, _height, _name.c_str(), NULL, NULL);

    if (!_window)
        throw std::runtime_error("Window couldn't be oppened.");
    glfwMakeContextCurrent(_window);

}

void GLApp::render()
{
    while (!glfwWindowShouldClose(_window)){
        glfwPollEvents();
        glClearColor(.2, .4, .6, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(_window);
    }
}

GLApp::~GLApp()
{
    if (_window != nullptr)
        glfwDestroyWindow(_window);
    glfwTerminate();
}
