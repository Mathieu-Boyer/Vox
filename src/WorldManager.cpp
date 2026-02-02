
#include "WorldManager.hpp"
#include "Chunk.hpp"

void WorldManager::loadChunks(){
    auto t1 = std::chrono::high_resolution_clock::now();

    std::array<int, 3> coordinates = {(int)(camera.getPosition().x / CHUNK_SIZE),  (int)(camera.getPosition().y / CHUNK_SIZE), (int)(camera.getPosition().z / CHUNK_SIZE)};
    for (int i = 0 - (MAX_RENDER / 2); i < (MAX_RENDER/2 + MAX_RENDER%2); i++)
        for (int j = 0 - (MAX_RENDER / 2); j < (MAX_RENDER/2 + MAX_RENDER%2); j++)
            for (int k = 0 - (MAX_RENDER / 2); k < (MAX_RENDER/2 + MAX_RENDER%2); k++){
                std::array<int, 3> toLoad(coordinates);
                toLoad[0] += i;
                toLoad[1] += j;
                toLoad[2] += k;
                auto it = world.find(toLoad) ;
                if (it != world.end()){

                    loadedChunks[i + MAX_RENDER/2][j + MAX_RENDER/2][k + MAX_RENDER/2].first = it->second.toMesh(*this);
                    loadedChunks[i + MAX_RENDER/2][j + MAX_RENDER/2][k + MAX_RENDER/2].second = &it->second;
                }
                else
                    loadedChunks[i + MAX_RENDER/2][j + MAX_RENDER/2][k + MAX_RENDER/2].second = nullptr;
            }

    auto t2 = std::chrono::high_resolution_clock::now();

    auto cpu_time = std::chrono::duration<double, std::milli>(t2 - t1).count();
        std::cout << "CPU2 : " << cpu_time << "ms\n";

}

WorldManager::WorldManager(/* args */) : 
    shader("shaders/default.vs", "shaders/default.fs"), camera({0,1,CHUNK_SIZE/2}), 

    cubeModel("models/cube.obj"), cubeMeshes(cubeModel.getMeshes())
{

    for (int i = 0 - (MAX_RENDER / 2); i < (MAX_RENDER/2 + MAX_RENDER%2); i++)
        for (int j = 0 - (MAX_RENDER / 2); j < (MAX_RENDER/2 + MAX_RENDER%2); j++)
            for (int k = 0 - (MAX_RENDER / 2); k < (MAX_RENDER/2 + MAX_RENDER%2); k++)
                world[(std::array<int, 3>){i, j, k}] = Chunk(i, j, k);

    shader.setInt("texArray", 0);
    loadChunks();

}

Camera &WorldManager::getCamera(){
    return camera;
}

const Camera &WorldManager::getCamera() const{
    return camera;
}

Chunk *WorldManager::getChunk(int x, int y, int z){

    std::array<int, 3> toFind = {x, y, z};
    auto it = world.find(toFind) ;
    if (it != world.end())
        return &it->second;
    else 
        return NULL;
}

void WorldManager::drawChunk(Mesh *mesh, Chunk &chunk){
    shader.use();
    const auto coordinates = chunk.getCoordinates();
    Renderable chunkInstance(*mesh);

     chunkInstance.transform._translation = {
                    coordinates[0] * CHUNK_SIZE,
                    coordinates[1] * CHUNK_SIZE,
                    coordinates[2] * CHUNK_SIZE
    };

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
                if (loadedChunks[i][j][k].second != nullptr){
                    drawChunk(loadedChunks[i][j][k].first.get(), *loadedChunks[i][j][k].second);
            }


}


WorldManager::~WorldManager()
{
}
