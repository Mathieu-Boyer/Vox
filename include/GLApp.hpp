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

    worldManager->loadChunks();
}


void cursorCallBack(GLFWwindow* window, double xpos, double ypos){
    WorldManager *worldManager = static_cast<WorldManager*>(glfwGetWindowUserPointer(window));
    Camera &camera = worldManager->getCamera();
    camera.setNewCursorPosition(xpos, ypos);
    camera.updateRotation();
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

    glfwSetKeyCallback(_window, keyCallBack);
    glfwSetCursorPosCallback(_window, cursorCallBack);

    glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

}

void GLApp::render()
{

    // Shaders shader("shaders/default.vs","shaders/default.fs");


    // (void)meshes;
    // Renderable cubeInstance(meshes, &texture);
    // Renderable cubeInstance2(meshes, &texture);

    // Camera camera({0,0,50});
    // glfwSetWindowUserPointer(_window, &camera); // 

    WorldManager worldManager;

    glfwSetWindowUserPointer(_window, &worldManager); // 

    // cubeInstance2.transform._translation = {1, 0, 0};
    // Chunk chunk0(0, 0, 0,shader, camera, meshes, texture);

    // Chunk chunk1(0, 0, 0,shader, camera, meshes, texture);
    // Chunk chunk2(1, 0, 0,shader, camera, meshes, texture);
    // Chunk chunk3(2, 0, 0,shader, camera, meshes, texture);
    while (!glfwWindowShouldClose(_window)){



        
        glfwPollEvents();
        glClearColor(.2, .2, .3, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // chunk0.drawChunk();

        // chunk1.drawChunk();
        // chunk2.drawChunk();
        // chunk3.drawChunk();
        worldManager.draw();
        // chunk1.drawChunk(shader);
        // shader.use();
        // cubeInstance.transform._rotation = {glfwGetTime() * 20, glfwGetTime() * 20, 1};
        // shader.setMat4("projection", projection);
        // shader.setMat4("view", view);
        // shader.setMat4("model", cubeInstance.transform.getModelMatrix());
        // cubeInstance.draw();

        // shader.setMat4("projection", projection);
        // shader.setMat4("view", view);
        // shader.setMat4("model", cubeInstance2.transform.getModelMatrix());
        // cubeInstance2.draw();
        glfwSwapBuffers(_window);
    }
}

GLApp::~GLApp()
{
    if (_window != nullptr)
        glfwDestroyWindow(_window);
    glfwTerminate();
}
