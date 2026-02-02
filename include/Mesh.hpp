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
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <vector>
#include <chrono>
struct Vertex
{
    glm::vec3 position;
    glm::vec2 textureCoordinates;
    int textureID;
    glm::vec3 normal;
};



class Mesh
{
    private:
        GLuint VBO = 0;
        GLuint VAO = 0;
        std::vector<Vertex> _vertices;
    public:
        Mesh(const std::vector<Vertex> vertices);

        Mesh(const Mesh&) = delete;
        Mesh& operator=(const Mesh&) = delete;
        Mesh(Mesh&&);
        Mesh& operator=(Mesh&&);

        void setup();
        void draw() const;
        ~Mesh();
};