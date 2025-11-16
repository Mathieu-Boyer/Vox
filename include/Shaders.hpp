#pragma once
#include <string>
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl3.h>
#include "GLFW/glfw3.h"
#include <fstream>
#include <iostream>

class Shaders
{
private:
    GLuint programId = 0;
    GLuint vertexShader = 0;
    GLuint fragmentShader = 0;

    void compileShader(GLuint &shader, const char *source, int type);
    void createShaderProgram();
    std::string loadFile(const std::string &path);
public:
    Shaders(const std::string &vertexPath , const std::string &fragmentPath);
    ~Shaders();

    GLuint getProgramId();
    void use();
};

Shaders::Shaders(const std::string &vertexPath , const std::string &fragmentPath)
{
    std::string vertexSource = loadFile(vertexPath);
    std::string fragmantSource = loadFile(fragmentPath);

    compileShader(vertexShader, vertexSource.c_str(), GL_VERTEX_SHADER);
    compileShader(fragmentShader, fragmantSource.c_str(), GL_FRAGMENT_SHADER);
    createShaderProgram();
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
