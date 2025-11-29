#pragma once
#include <array>
#include <map>
#include "Chunk.hpp"
#include "Shaders.hpp"
#include "Camera.hpp"
#include "Model.hpp"

#define MAX_RENDER 4

class WorldManager
{
private:
    std::map<std::array<int, 3>, Chunk> world;
    std::array<std::array<std::array<Chunk*, MAX_RENDER> , MAX_RENDER>, MAX_RENDER > loadedChunks;
    Shaders shader;
    Camera camera;
    const std::array<Texture, 2> textures;
    Model cubeModel;
    const std::vector<Mesh> &cubeMeshes;
    void drawChunk(Chunk *chunk);


public:
    WorldManager(/* args */);
    void draw();
    void loadChunks();
    Camera &getCamera();
    const Camera &getCamera() const;
    ~WorldManager();
};

void WorldManager::loadChunks(){
    std::array<int, 3> coordinates = {(int)(camera.getPosition().x / CHUNK_SIZE),  (int)(camera.getPosition().y / CHUNK_SIZE), (int)(camera.getPosition().z / CHUNK_SIZE)};
    for (int i = 0 - (MAX_RENDER / 2); i < (MAX_RENDER/2 + i%2); i++)
        for (int j = 0 - (MAX_RENDER / 2); j < (MAX_RENDER/2 + j%2); j++)
            for (int k = 0 - (MAX_RENDER / 2); k < (MAX_RENDER/2 + k%2); k++){
                std::array<int, 3> toLoad(coordinates);
                toLoad[0] += i;
                toLoad[1] += j;
                toLoad[2] += k;
                auto it = world.find(toLoad) ;
                if (it != world.end())
                    loadedChunks[i + MAX_RENDER/2][j + MAX_RENDER/2][k + MAX_RENDER/2] = &it->second;
                else
                    loadedChunks[i + MAX_RENDER/2][j + MAX_RENDER/2][k + MAX_RENDER/2] = nullptr;
            }
}

WorldManager::WorldManager(/* args */) : 
    shader("shaders/default.vs", "shaders/default.fs"), camera({0,0,50}), 
    textures({Texture("textures/dirt.png"), Texture("textures/stone.png")}),
    cubeModel("models/cube.obj"), cubeMeshes(cubeModel.getMeshes())
{

    for (int i = -20; i < 20; i++)
        for (int j = -20; j < 20; j++)
            for (int k = -20; k < 20; k++)
                world[(std::array<int, 3>){i, j, k}] = Chunk(i, j, k);
    loadChunks();
}

Camera &WorldManager::getCamera(){
    return camera;
}

const Camera &WorldManager::getCamera() const{
    return camera;
}


void WorldManager::drawChunk(Chunk *chunk){
    shader.use();
    // const auto &data = chunk->getData();
    // const auto coordinates = chunk->getCoordinates();

    // for (unsigned int i = 0; i < CHUNK_SIZE; i++)
    //     for (unsigned int j = 0; j < CHUNK_SIZE; j++)
    //         for (unsigned int k = 0; k < CHUNK_SIZE; k++){
    //             if (data[i][j][k] == AIR)
    //                 continue;
    //             Renderable cubeInstance(cubeMeshes, &textures[data[i][j][k]]);
    //             cubeInstance.transform._translation = {
    //                 coordinates[0] * CHUNK_SIZE + i,
    //                 coordinates[1] * CHUNK_SIZE + j,
    //                 coordinates[2] * CHUNK_SIZE + k
    //             };

    //             shader.setMat4("projection", camera.getProjectionMatrix());
    //             shader.setMat4("view", camera.getViewMatrix());
    //             shader.setMat4("model", cubeInstance.transform.getModelMatrix());
    //             cubeInstance.draw();
    //         }


    Mesh chunkMesh = chunk->toMesh();
    Renderable chunkInstance(chunkMesh, &textures[0]);



    //  chunkInstance.transform._translation = {
    //                 coordinates[0] * CHUNK_SIZE,
    //                 coordinates[1] * CHUNK_SIZE,
    //                 coordinates[2] * CHUNK_SIZE
    // };
    // chunkInstance.transform._translation = chunk->getCoordinates();
    shader.setMat4("projection", camera.getProjectionMatrix());
    shader.setMat4("view", camera.getViewMatrix());
    shader.setMat4("model", chunkInstance.transform.getModelMatrix());
    chunkInstance.draw();
    
}

void WorldManager::draw(){

    camera.updatePosition();
    for (unsigned int i = 0 ; i < MAX_RENDER; i++)
        for (unsigned int j = 0 ; j < MAX_RENDER; j++)
            for (unsigned int k = 0 ; k < MAX_RENDER; k++)
                if (loadedChunks[i][j][k] != nullptr){
                    drawChunk(loadedChunks[i][j][k]);
            }


}


WorldManager::~WorldManager()
{
}
