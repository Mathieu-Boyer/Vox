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