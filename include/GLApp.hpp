#pragma once

#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl3.h>
#include "GLFW/glfw3.h"
#include <string>
#include "Shaders.hpp"
#include "Texture.hpp"
#include "Model.hpp"
#include "Mesh.hpp"
#include "Renderable.hpp"
#include "Camera.hpp"




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

    glEnable(GL_DEPTH_TEST);

}

void GLApp::render()
{
    Texture texture("textures/dirt.png");
    Shaders shader("shaders/default.vs","shaders/default.fs");
    Model model("models/cube.obj");

    const std::vector<Mesh> &meshes = model.getMeshes();
    Renderable cubeInstance(meshes, &texture);
    Renderable cubeInstance2(meshes, &texture);

    Camera camera({1,0,5});

    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 projection = camera.getProjectionMatrix();

    
    cubeInstance2.transform._translation = {1, 0, 0};
    while (!glfwWindowShouldClose(_window)){
        glfwPollEvents();
        glClearColor(.2, .2, .3, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader.use();
        // cubeInstance.transform._rotation = {glfwGetTime() * 20, glfwGetTime() * 20, 1};
        shader.setMat4("projection", projection);
        shader.setMat4("view", view);
        shader.setMat4("model", cubeInstance.transform.getModelMatrix());
        cubeInstance.draw();

        shader.setMat4("projection", projection);
        shader.setMat4("view", view);
        shader.setMat4("model", cubeInstance2.transform.getModelMatrix());
        cubeInstance2.draw();
        glfwSwapBuffers(_window);
    }
}

GLApp::~GLApp()
{
    if (_window != nullptr)
        glfwDestroyWindow(_window);
    glfwTerminate();
}
