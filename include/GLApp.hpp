#pragma once

#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#endif
#ifdef __linux__
#include <GL/gl.h>
#include "utils.hpp"
#endif



#include "GLFW/glfw3.h"
#include <string>
#include "Shaders.hpp"
#include "Texture.hpp"
#include "Model.hpp"
#include "Mesh.hpp"
#include "Renderable.hpp"
#include "Camera.hpp"
#include "Chunk.hpp"
#include "WorldManager.hpp"



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

void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods){
    (void)mods;
    (void)scancode;

    WorldManager *worldManager = static_cast<WorldManager*>(glfwGetWindowUserPointer(window));

    Camera &camera = worldManager->getCamera();

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (key == GLFW_KEY_Q && (action == GLFW_PRESS || action == GLFW_REPEAT))
        camera.moveFlags[0] = -.05;
    if (key == GLFW_KEY_Q && action == GLFW_RELEASE)
        camera.moveFlags[0] = 0;
    if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT))
        camera.moveFlags[0] = +.05;
    if (key == GLFW_KEY_D && action == GLFW_RELEASE)
        camera.moveFlags[0] = 0;

    if (key == GLFW_KEY_SPACE && (action == GLFW_PRESS || action == GLFW_REPEAT))
        camera.moveFlags[1] = +.05;
    if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE)
        camera.moveFlags[1] = 0;
    if (key == GLFW_KEY_LEFT_SHIFT && (action == GLFW_PRESS || action == GLFW_REPEAT))
        camera.moveFlags[1] = -.05;
    if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_RELEASE)
        camera.moveFlags[1] = 0;

    if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT))
        camera.moveFlags[2] = +.05;
    if (key == GLFW_KEY_W && action == GLFW_RELEASE)
        camera.moveFlags[2] = 0;
    if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT))
        camera.moveFlags[2] = -.05;
    if (key == GLFW_KEY_S && action == GLFW_RELEASE)
        camera.moveFlags[2] = 0;

}


void cursorCallBack(GLFWwindow* window, double xpos, double ypos){
    WorldManager *worldManager = static_cast<WorldManager*>(glfwGetWindowUserPointer(window));
    Camera &camera = worldManager->getCamera();
    camera.setNewCursorPosition(xpos, ypos);
    camera.updateRotation();
}

void GLApp::init(){
    if (!glfwInit())
        throw std::runtime_error("glfwInit failed");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    _window = glfwCreateWindow(_width, _height, _name.c_str(), NULL, NULL);

    if (!_window)
        throw std::runtime_error("Window couldn't be oppened.");

    glfwMakeContextCurrent(_window);
    if (glfwGetCurrentContext() == nullptr)
        throw std::runtime_error("Failed to create OpenGL context");


    std::cout << "GL version: " << glGetString(GL_VERSION) << "\n";
    glEnable(GL_DEPTH_TEST);

    glfwSetKeyCallback(_window, keyCallBack);
    glfwSetCursorPosCallback(_window, cursorCallBack);

    glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

}

void GLApp::render()
{
    WorldManager worldManager;
    glfwSetWindowUserPointer(_window, &worldManager);
    // glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    // unsigned int i = 0;
    while (!glfwWindowShouldClose(_window)){
        glfwPollEvents();
        glClearColor(.2, .1, .2, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        worldManager.loadChunks();
        
        // i++;

        worldManager.draw();
        glfwSwapBuffers(_window);
    }

}

GLApp::~GLApp()
{
    if (_window != nullptr){
        glfwMakeContextCurrent(NULL);
        glfwDestroyWindow(_window);
    }
    glfwTerminate();
}
