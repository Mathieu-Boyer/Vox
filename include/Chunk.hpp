#pragma once
#define CHUNK_SIZE 16
#include "Block.hpp"
#include "Shaders.hpp"
#include "Camera.hpp"
#include "Mesh.hpp"
#include "Texture.hpp"
#include "Renderable.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <array>
class Chunk
{
private:
    int x,y,z;
    std::array<std::array<std::array<int, CHUNK_SIZE>, CHUNK_SIZE>, CHUNK_SIZE> _data;
    void buildCubeVertices(std::vector<Vertex> &vertices, std::array<float , 3> &blockPosition);
public:
    Chunk();
    Chunk(int x, int y, int z);
    const std::array<int , 3>  getCoordinates() const;
    std::array<std::array<std::array<int, CHUNK_SIZE>, CHUNK_SIZE>, CHUNK_SIZE> getData() const;

    Mesh toMesh();
    ~Chunk();
};


Chunk::Chunk(): x(0), y(0), z(0){
    for (unsigned int i = 0; i < CHUNK_SIZE; i++)
        for (unsigned int j = 0; j < CHUNK_SIZE; j++)
            for (unsigned int k = 0; k < CHUNK_SIZE; k++)
                _data[i][j][k] = DIRT;
}

Chunk::Chunk(int x, int y, int z) : x(x),y(y),z(z)
{
    for (unsigned int i = 0; i < CHUNK_SIZE; i++)
        for (unsigned int j = 0; j < CHUNK_SIZE; j++)
            for (unsigned int k = 0; k < CHUNK_SIZE; k++)
                _data[i][j][k] = DIRT;
}

const std::array<int , 3> Chunk::getCoordinates() const{
    return {x,y,z};
}

std::array<std::array<std::array<int, CHUNK_SIZE>, CHUNK_SIZE>, CHUNK_SIZE> Chunk::getData() const{
    return _data;
}

void Chunk::buildCubeVertices(std::vector<Vertex> &vertices, std::array<float, 3> &block){
    std::array<glm::vec3, 8> blockVertices = {{
        glm::vec3(block[0]     , block[1]     , block[2]),    
        glm::vec3(block[0] + 1 , block[1]     , block[2]),    
        glm::vec3(block[0] + 1 , block[1] + 1 , block[2]),    
        glm::vec3(block[0]     , block[1] + 1 , block[2]),    
        glm::vec3(block[0]     , block[1]     , block[2] + 1),
        glm::vec3(block[0] + 1 , block[1]     , block[2] + 1),
        glm::vec3(block[0] + 1 , block[1] + 1 , block[2] + 1),
        glm::vec3(block[0]     , block[1] + 1 , block[2] + 1) 
    }};
    
    std::array<glm::vec2, 4> textureCoords = {{
        glm::vec2(0.0f, 0.0f),
        glm::vec2(1.0f, 0.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec2(0.0f, 1.0f) 
    }};
    
    std::array<std::array<std::array<int, 2>, 3>, 12> triangles = {{
        {{{0,0}, {1,1}, {2,2}}},
        {{{0,0}, {2,2}, {3,3}}},
        {{{4,0}, {6,2}, {5,1}}},
        {{{4,0}, {7,3}, {6,2}}},
        {{{0,0}, {5,2}, {1,1}}},
        {{{0,0}, {4,3}, {5,2}}},
        {{{3,0}, {2,1}, {6,2}}},
        {{{3,0}, {6,2}, {7,3}}},
        {{{1,0}, {5,1}, {6,2}}},
        {{{1,0}, {6,2}, {2,3}}},
        {{{0,0}, {3,3}, {7,2}}},
        {{{0,0}, {7,2}, {4,1}}}
    }};
    
    for (const auto& triangle : triangles) {
        for (int i = 0; i < 3; i++) {
            Vertex vertex;
            vertex.position = blockVertices[triangle[i][0]];
            vertex.textureCoordinates = textureCoords[triangle[i][1]];
            vertices.push_back(vertex);
        }
    }
}


Mesh Chunk::toMesh(){
    std::vector<Vertex> vertices;
    for (unsigned int i = 0; i < CHUNK_SIZE; i++)
        for (unsigned int j = 0; j < CHUNK_SIZE; j++)
            for (unsigned int k = 0; k < CHUNK_SIZE; k++){
                std::array<float , 3> blockPosition = {(float)x * CHUNK_SIZE + i, (float)y * CHUNK_SIZE + j,(float)z * CHUNK_SIZE + k};
                buildCubeVertices(vertices, blockPosition);
            }

    return Mesh(vertices);
}

Chunk::~Chunk()
{
}
