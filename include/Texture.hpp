#pragma once

#include <string>
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

// #define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"


class Texture
{
private:
    GLuint texture;

public:
    Texture(const std::string &path);
    void bind(unsigned int unit = 0) const;
    ~Texture();
};