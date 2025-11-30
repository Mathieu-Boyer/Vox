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

Shaders::Shaders(const char *vertexPath , const char *fragmentPath)
{
    std::string vertexSource = loadFile(vertexPath);
    std::string fragmantSource = loadFile(fragmentPath);

    compileShader(vertexShader, vertexSource.c_str(), GL_VERTEX_SHADER);
    compileShader(fragmentShader, fragmantSource.c_str(), GL_FRAGMENT_SHADER);
    createShaderProgram();
}

GLint Shaders::getLocation(const std::string &location){
    return glGetUniformLocation(programId, location.c_str());
}


void Shaders::use(){
    glUseProgram(getProgramId());
}

GLuint Shaders::getProgramId(){
    return programId;
}

std::string Shaders::loadFile(const std::string &path){
    std::ifstream file (path, std::ios::binary);
    std::string content;
    std::string line;

    while (getline(file, line))
        content += line + "\n";

    return content;
}

void Shaders::setInt(const std::string &location, int value){
    glUniform1i(getLocation(location), value); 
}

void  Shaders::setFloat(const std::string &location, float value){;
    glUniform1f(getLocation(location), value); 
}
void Shaders::setBool(const std::string &location, bool value){
    glUniform1i(getLocation(location), value); 
}

void Shaders::setMat4(const std::string &location, const glm::mat4 &value){
    glUniformMatrix4fv(getLocation(location),1, GL_FALSE, (const GLfloat *)glm::value_ptr(value));
}
void Shaders::setVec3(const std::string &location, const glm::vec3 &value){
    glUniform3fv(getLocation(location), 1, (const GLfloat *)glm::value_ptr(value));
}

void Shaders::createShaderProgram(){
    programId = glCreateProgram();
    glAttachShader(programId, vertexShader);
    glAttachShader(programId, fragmentShader);
    glLinkProgram(programId);
}

void Shaders::compileShader(GLuint &shader, const char *source, int type){
    shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar infoLog[1024];
        glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
        throw std::runtime_error(std::string("ERROR: Shader compilation failed\n") + infoLog + '\n');
    } else
        std::cout << "Shader compiled successfully" << std::endl;
}

Shaders::~Shaders()
{
    if (vertexShader) glDeleteShader(vertexShader);
    if (fragmentShader) glDeleteShader(fragmentShader);
}
