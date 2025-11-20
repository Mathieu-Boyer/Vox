#pragma once
#include <array>
#include <map>
#include "Chunk.hpp"
#include "Shaders.hpp"
#include "Camera.hpp"
#include "Model.hpp"

#define MAX_RENDER 5

class WorldManager
{
private:
    std::map<std::array<int, 3>, Chunk> world;
    std::array<Chunk*, MAX_RENDER> loadedChunks;
    Shaders shader;
    Camera camera;
    const std::array<Texture, 1> textures;
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
    std::array<int, 3> coordinates = {(int)camera.getPosition().x / CHUNK_SIZE,  0, 0};
    for (int i = 0 - (MAX_RENDER / 2); i <= MAX_RENDER/2; i++){
        std::array<int, 3> toLoad(coordinates);
        toLoad[0] += i;
        auto it = world.find(toLoad) ;
        if (it != world.end())
            loadedChunks[i + MAX_RENDER/2] = &it->second;
        else 
            loadedChunks[i + MAX_RENDER/2] = nullptr;
    }
}

WorldManager::WorldManager(/* args */) : 
    shader("shaders/default.vs", "shaders/default.fs"), camera({0,0,50}), 
    textures({Texture("textures/dirt.png")}),
    cubeModel("models/cube.obj"), cubeMeshes(cubeModel.getMeshes())
{


    for (int i = 0 - (MAX_RENDER / 2); i < 20; i++)
        world[(std::array<int, 3>){(int)i, 0, 0}] = Chunk((int)i, 0, 0);
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
    const auto &data = chunk->getData();
    const auto &coordinates = chunk->getCoordinates();

    for (unsigned int i = 0; i < CHUNK_SIZE; i++)
        for (unsigned int j = 0; j < CHUNK_SIZE; j++)
            for (unsigned int k = 0; k < CHUNK_SIZE; k++){
                Renderable cubeInstance(cubeMeshes, &textures[data[i][j][k]]);
                cubeInstance.transform._translation = {
                    coordinates[0] * CHUNK_SIZE + i,
                    coordinates[1] * CHUNK_SIZE + j,
                    coordinates[2] * CHUNK_SIZE + k
                };

                shader.setMat4("projection", camera.getProjectionMatrix());
                shader.setMat4("view", camera.getViewMatrix());
                shader.setMat4("model", cubeInstance.transform.getModelMatrix());
                cubeInstance.draw();
            }
}

void WorldManager::draw(){

    camera.updatePosition();
    for (auto chunk : loadedChunks)
        if (chunk != nullptr){
            drawChunk(chunk);
    }


}


WorldManager::~WorldManager()
{
}
