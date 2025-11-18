#pragma once
#define CHUNK_SIZE 16
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
    Shaders &shader;
    Camera &camera;
    const std::vector<Mesh> &meshes;
    Texture &texture;
    std::array<std::array<std::array<int, CHUNK_SIZE>, CHUNK_SIZE>, CHUNK_SIZE> _data;

public:
    Chunk(int x, int y, int z, Shaders &shader, Camera &camera, const std::vector<Mesh> &meshes, Texture &texture);
    void drawChunk();
    ~Chunk();
};

Chunk::Chunk(int x, int y, int z, Shaders &shader, Camera &camera, const std::vector<Mesh> &meshes, Texture &texture) : x(x),y(y),z(z), shader(shader), camera(camera), meshes(meshes), texture(texture)
{
    for (unsigned int i = 0; i < CHUNK_SIZE; i++)
        for (unsigned int j = 0; j < CHUNK_SIZE; j++)
            for (unsigned int k = 0; k < CHUNK_SIZE; k++)
                _data[i][j][k] = DIRT;
}


void Chunk::drawChunk(){

    shader.use();

    for (unsigned int i = 0; i < CHUNK_SIZE; i++)
        for (unsigned int j = 0; j < CHUNK_SIZE; j++)
            for (unsigned int k = 0; k < CHUNK_SIZE; k++){
                Renderable cubeInstance(meshes, &texture);

                cubeInstance.transform._translation = {x*CHUNK_SIZE + i,y*CHUNK_SIZE +j,z*CHUNK_SIZE +k};

                shader.setMat4("projection", camera.getProjectionMatrix());
                shader.setMat4("view", camera.getViewMatrix());
                shader.setMat4("model", cubeInstance.transform.getModelMatrix());
                cubeInstance.draw();
            }

}


Chunk::~Chunk()
{
}
