#pragma once
#define CHUNK_SIZE 6
#include "Block.hpp"
#include "Shaders.hpp"
#include "Camera.hpp"
#include "Mesh.hpp"
#include "Texture.hpp"
#include "Renderable.hpp"
#include <array>
class Chunk
{
private:
    int x,y,z;
    std::array<std::array<std::array<int, CHUNK_SIZE>, CHUNK_SIZE>, CHUNK_SIZE> _data;

public:
    Chunk();
    Chunk(int x, int y, int z);
    const std::array<int , 3>  getCoordinates() const;
    std::array<std::array<std::array<int, CHUNK_SIZE>, CHUNK_SIZE>, CHUNK_SIZE> getData() const;
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
                _data[i][j][k] = AIR + i % 3;
}

const std::array<int , 3> Chunk::getCoordinates() const{
    return {x,y,z};
}

std::array<std::array<std::array<int, CHUNK_SIZE>, CHUNK_SIZE>, CHUNK_SIZE> Chunk::getData() const{
    return _data;
}


Chunk::~Chunk()
{
}
