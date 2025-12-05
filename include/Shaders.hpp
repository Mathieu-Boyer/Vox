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
#include <fstream>
#include <iostream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>


class Shaders
{
private:
    GLuint programId = 0;
    GLuint vertexShader = 0;
    GLuint fragmentShader = 0;

    void compileShader(GLuint &shader, const char *source, int type);
    void createShaderProgram();
    std::string loadFile(const std::string &path);

    GLint getLocation(const std::string &location);
public:
    Shaders(const char *vertexPath , const char *fragmentPath);
    ~Shaders();

    GLuint getProgramId();

    void setInt(const std::string &location, int value);
    void setFloat(const std::string &location, float value);
    void setBool(const std::string &location, bool value);
    void setMat4(const std::string &location, const glm::mat4 &value);
    void setVec3(const std::string &location, const glm::vec3 &value);
    void use();
};