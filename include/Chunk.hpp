#pragma once
#define CHUNK_SIZE 5
#include "Block.hpp"
#include "Shaders.hpp"
#include "Camera.hpp"
// #include "Mesh.hpp"
// #include "WorldManager.hpp"
#include "Texture.hpp"
#include "Renderable.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <array>
#include <memory>
#include <chrono>

class WorldManager;

constexpr std::array<glm::vec2, 4> textureCoords = {{
    glm::vec2(0.0f, 0.0f),
    glm::vec2(1.0f, 0.0f),
    glm::vec2(1.0f, 1.0f),
    glm::vec2(0.0f, 1.0f) 
}};

constexpr  std::array<std::array<std::array<std::array<int, 2>, 3>, 2>, 6> faces = {{
    {{
        {{{0,0}, {1,1}, {2,2}}},
        {{{0,0}, {2,2}, {3,3}}},
    }},

    {{
        {{{4,0}, {6,1}, {5,2}}},
        {{{4,0}, {7,2}, {6,3}}},
    }},

    {{
        {{{0,0}, {5,1}, {1,2}}},
        {{{0,0}, {4,2}, {5,3}}},
    }},

    {{
        {{{3,0}, {2,1}, {6,2}}},
        {{{3,0}, {6,2}, {7,3}}},
    }},

    {{ 
        {{{0,0}, {3,1}, {7,2}}},
        {{{0,0}, {7,2}, {4,3}}},
    }},

    {{
        {{{1,0}, {5,1}, {6,2}}},
        {{{1,0}, {6,2}, {2,3}}},
    }}


}};


class Chunk
{
private:
    int _x = 0;
    int _y = 0;
    int _z = 0;
    std::array<std::array<std::array<int, CHUNK_SIZE>, CHUNK_SIZE>, CHUNK_SIZE> _data;
    int occlusionCulling(unsigned int axis, std::array<int , 3> &blockPosition, unsigned int currentFace, WorldManager &worldManager);
    void buildTriangles(std::vector<Vertex>& vertices, int face, int layer, int x, int y, int height, int width);
    void greedyMesh(std::vector<Vertex>& vertices, std::array<std::array<int, CHUNK_SIZE>, CHUNK_SIZE> &plane);
public:
    Chunk();
    Chunk(int x, int y, int z);
    const std::array<int , 3>  getCoordinates() const;
    std::array<std::array<std::array<int, CHUNK_SIZE>, CHUNK_SIZE>, CHUNK_SIZE> getData() const;
    int getBlockAt(int x, int y , int z);
    std::unique_ptr<Mesh> toMesh(WorldManager &wordManager);
    ~Chunk();
};
