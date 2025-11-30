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



constexpr std::array<glm::vec2, 4> textureCoords = {{
    glm::vec2(0.0f, 0.0f),
    glm::vec2(1.0f, 0.0f),
    glm::vec2(1.0f, 1.0f),
    glm::vec2(0.0f, 1.0f) 
}};

constexpr std::array<std::array<std::array<int, 2>, 3>, 12> triangles = {{
    // front
    {{{0,0}, {1,1}, {2,2}}},
    {{{0,0}, {2,2}, {3,3}}},
    
    // back
    {{{4,0}, {6,2}, {5,1}}},
    {{{4,0}, {7,3}, {6,2}}},

    // down
    {{{0,0}, {5,2}, {1,1}}},
    {{{0,0}, {4,3}, {5,2}}},

    // up
    {{{3,0}, {2,1}, {6,2}}},
    {{{3,0}, {6,2}, {7,3}}},

    // left 
    {{{0,0}, {3,3}, {7,2}}},
    {{{0,0}, {7,2}, {4,1}}},

    // right
    {{{1,0}, {5,1}, {6,2}}},
    {{{1,0}, {6,2}, {2,3}}}


}};


class Chunk
{
private:
    int x = 0;
    int y = 0;
    int z = 0;
    std::array<std::array<std::array<int, CHUNK_SIZE>, CHUNK_SIZE>, CHUNK_SIZE> _data;
    void buildCubeVertices(std::vector<Vertex> &vertices, std::array<float , 3> &blockPosition);
public:
    Chunk();
    Chunk(int x, int y, int z);
    const std::array<int , 3>  getCoordinates() const;
    std::array<std::array<std::array<int, CHUNK_SIZE>, CHUNK_SIZE>, CHUNK_SIZE> getData() const;
    int getBlockAt(int x, int y , int z);
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
            for (unsigned int k = 0; k < CHUNK_SIZE; k++){
                    _data[i][j][k] = y == 1 ? AIR : DIRT;
            }
    
}

const std::array<int , 3> Chunk::getCoordinates() const{
    // std::cout << x <<y <<z << "\n";
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
    

    unsigned int i = 0;
    while (i < triangles.size()) {

        if ((i < 2 && block[2] > 0 && getBlockAt(block[0], block[1], block[2] - 1) != AIR) || 
        (i >=  2 && i < 4 && block[2] < CHUNK_SIZE - 1 && getBlockAt(block[0], block[1], block[2] + 1) != AIR) || 
        (i >=  4 && i < 6 && block[1] > 0 && getBlockAt(block[0], block[1] - 1, block[2]) != AIR) || 
        (i >=  6 && i < 8 && block[1] < CHUNK_SIZE - 1 && getBlockAt(block[0], block[1] + 1, block[2]) != AIR) || 
        (i >=  8 && i < 10 && block[0] > 0 && getBlockAt(block[0] - 1, block[1], block[2]) != AIR) ||
        (i >= 10 && i < 12 && block[0] < CHUNK_SIZE - 1 && getBlockAt(block[0] + 1, block[1], block[2]) != AIR)) {
            i+=2;
            continue;
        }

    for (int tri = 0; tri < 2; tri++) {  // Process 2 triangles per face
        for (int j = 0; j < 3; j++) {
            Vertex vertex;
            vertex.position = blockVertices[triangles[i][j][0]];
            vertex.textureCoordinates = textureCoords[triangles[i][j][1]];
            vertices.push_back(vertex);
        }
        i++;
    }
    }
}


int Chunk::getBlockAt(int x, int y , int z){
    return _data[x][y][z];
}


Mesh Chunk::toMesh(){
    std::vector<Vertex> vertices;
    for (unsigned int i = 0; i < CHUNK_SIZE; i++)
        for (unsigned int j = 0; j < CHUNK_SIZE; j++)
            for (unsigned int k = 0; k < CHUNK_SIZE; k++){
                // std::cout << i << " " << j << " " << k << "\n" ;
                if ( _data[i][j][k] == AIR)
                    continue;
                std::array<float , 3> blockPosition = {(float)i,(float)j,(float)k};
                buildCubeVertices(vertices, blockPosition);
            }

    return Mesh(vertices);
}

Chunk::~Chunk()
{
}
