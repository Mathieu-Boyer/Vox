#pragma once

#include <string>
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl3.h>
#include "GLFW/glfw3.h"
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "../stb/stb_image.h"

class Texture
{
private:
    GLuint texture;

public:
    Texture(const std::string &path);
    void bind(unsigned int unit = 0) const;
    ~Texture();
};

Texture::Texture(const std::string &path)
{

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (!data)
        throw std::runtime_error("Unable to load the texture.");
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
}
void Texture::bind(unsigned int unit) const{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, texture);
}
Texture::~Texture()
{
    glDeleteTextures(1, &texture);
}
