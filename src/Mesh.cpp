#include "Mesh.hpp"
#include "iostream"



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

void Mesh::draw() const{
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, _vertices.size());
    glBindVertexArray(0);

}

void Mesh::setup(){

    // auto t1 = std::chrono::high_resolution_clock::now();
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
    // auto t2 = std::chrono::high_resolution_clock::now();


    // auto gpu_time = std::chrono::duration<double, std::milli>(t2 - t1).count();
    
    // std::cout << "GPU: " << gpu_time << "ms\n";

}


Mesh::~Mesh()
{
    if (VBO) glDeleteBuffers(1, &VBO);
    if (VAO) glDeleteVertexArrays(1, &VAO);
}
