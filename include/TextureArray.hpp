#pragma once 
#include <array>
#include <string>
#include <stdexcept>
#include <iostream>
#include "stb/stb_image.h"

#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <OpenGL/gl3.h>
#endif
#ifdef __linux__
#include <GL/gl.h>
#include "utils.hpp"
#endif

#define RGBA 4
class TextureArray
{
private:
    GLuint _textureArray;
    int _texturesAmount;
public:
    TextureArray(std::array<std::string, 2> textures);
    void bind(unsigned int unit) const;
    ~TextureArray();
};

