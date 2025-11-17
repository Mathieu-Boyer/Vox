#pragma once
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl3.h>
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

struct Vertex
{
    glm::vec3 position;
    glm::vec2 textureCoordinates;
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
        void draw();
        ~Mesh();
};

Mesh::Mesh(const std::vector<Vertex> vertices) : _vertices(vertices){

    setup();
}

Mesh::Mesh(Mesh&& src){
    _vertices = std::move(src._vertices);
    VAO = src.VAO;
    VBO = src.VBO;
    

    src.VAO = 0;
    src.VBO = 0;
}
Mesh& Mesh::operator=(Mesh&& src){
    _vertices = std::move(src._vertices);
    VAO = src.VAO;
    VBO = src.VBO;
    
    src.VAO = 0;
    src.VBO = 0;

    return *this;
}

void Mesh::draw(){
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, _vertices.size());
    glBindVertexArray(0);

}

void Mesh::setup(){
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * _vertices.size(), &_vertices[0], GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3 , GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2 , GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, textureCoordinates));
    glEnableVertexAttribArray(1);
    
    glVertexAttribPointer(2, 3 , GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal));
    glEnableVertexAttribArray(2);
}


Mesh::~Mesh()
{
    if (VBO) glDeleteBuffers(1, &VBO);
    if (VAO) glDeleteVertexArrays(1, &VAO);
}
