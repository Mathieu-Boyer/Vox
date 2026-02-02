#pragma once
#include <array>
#include <map>
// #include "Chunk.hpp"
#include "Shaders.hpp"
#include "Camera.hpp"
#include "Texture.hpp"
#include "Model.hpp"
#include <chrono>
class Chunk;

#define MAX_RENDER 5

class WorldManager
{
private:
    std::map<std::array<int, 3>, Chunk> world;
    std::array<std::array<std::array<std::pair<std::unique_ptr<Mesh>, Chunk*> , MAX_RENDER> , MAX_RENDER>, MAX_RENDER > loadedChunks;
    Shaders shader;
    Camera camera;
    // const std::array<Texture, 2> textures;
    Model cubeModel;
    const std::vector<Mesh> &cubeMeshes;
    void drawChunk(Mesh *mesh, Chunk &chunk);


public:
    WorldManager(/* args */);
    void draw();
    void loadChunks();
    Camera &getCamera();
    const Camera &getCamera() const;
    ~WorldManager();
    bool wireView = false;
    Chunk *getChunk(int x, int y, int z);

};
