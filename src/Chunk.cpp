#include "Chunk.hpp"
#include "WorldManager.hpp"

Chunk::Chunk(): _x(0), _y(0), _z(0){
    for (unsigned int i = 0; i < CHUNK_SIZE; i++)
        for (unsigned int j = 0; j < CHUNK_SIZE; j++)
            for (unsigned int k = 0; k < CHUNK_SIZE; k++)
                _data[i][j][k] = DIRT;
}

Chunk::Chunk(int x, int y, int z) :_x(x),_y(y),_z(z)
{
    for (unsigned int i = 0; i < CHUNK_SIZE; i++)
        for (unsigned int j = 0; j < CHUNK_SIZE; j++)
            for (unsigned int k = 0; k < CHUNK_SIZE; k++){
                    _data[i][j][k] =   y == 1 ? AIR : DIRT;//j == 1 ? AIR :
            }
    
}

const std::array<int , 3> Chunk::getCoordinates() const{
    return {_x,_y,_z};
}

std::array<std::array<std::array<int, CHUNK_SIZE>, CHUNK_SIZE>, CHUNK_SIZE> Chunk::getData() const{
    return _data;
}

int Chunk::occlusionCulling(unsigned int axis, std::array<int, 3> &block , unsigned int currentFace, WorldManager &worldManager){
    auto toFind(block);
    std::array<int , 3> chunkToFind = {_x, _y, _z};

    if (currentFace % 2 == 0){
        toFind[axis] -= 1;
        chunkToFind[axis] -= 1;
    }
    else{
        toFind[axis] += 1;
        chunkToFind[axis] += 1 ;
    }

    if ((toFind[axis] >= 0) && (toFind[axis] < CHUNK_SIZE)){
        if (getBlockAt(toFind[0], toFind[1], toFind[2]) != AIR)
            return -1;
        return getBlockAt(block[0], block[1], block[2]);
    }

    Chunk *chunkAt = worldManager.getChunk(chunkToFind[0],chunkToFind[1],chunkToFind[2]);

    if (toFind[axis] == -1)
        toFind[axis] = CHUNK_SIZE - 1;
    else
        toFind[axis] = 0;

    if (chunkAt && chunkAt->getBlockAt(toFind[0], toFind[1], toFind[2]) != AIR)
        return -1;
    
    return getBlockAt(block[0], block[1], block[2]);

}

int Chunk::getBlockAt(int x, int y , int z){
    return _data[x][y][z];
}

void Chunk::buildTriangles(std::vector<Vertex>& vertices, int face, int layer, int x, int y, int height, int width){
    std::array<std::array<glm::vec3, 3>, 3> triangles;
    if (face < 2)
        triangles = {{
            {{
                {x        , y         , layer + (face % 2)},
                {x + width, y         , layer + (face % 2)},
                {x + width, y + height, layer + (face % 2)},
            }},
            {{
                {x        , y         , layer + (face % 2)},
                {x + width, y + height, layer + (face % 2)},
                {x        , y + height, layer + (face % 2)},
            }}
        }};                  
    else if (face < 4)
        triangles = {{
            {{
                { x          ,  layer + (face % 2),  y},
                { x  + width ,  layer + (face % 2),  y },
                { x  + width ,  layer + (face % 2),  y  + height},
            }},
            {{
                { x         , layer + (face % 2),  y},
                { x + width , layer + (face % 2),  y  + height},
                { x         , layer + (face % 2),  y  + height},
            }},
        }};
    else if (face < 6)
        triangles = {{
            {{
                {layer + (face % 2) ,y          , x},
                {layer + (face % 2), y          , x + width},
                {layer + (face % 2) ,y + height , x + width},
            }},
            {{
                {layer + (face % 2) ,y          , x},
                {layer + (face % 2) ,y + height , x + width},
                {layer + (face % 2), y + height , x},
            }},
        }};

    for (int tri = 0; tri < 2 ; tri++){

        for (int vert = 0; vert < 3 ; vert++){
            Vertex vertex;
            vertex.position = triangles[tri][vert];
            vertex.textureCoordinates = (textureCoords[faces[face][tri][vert][1]]);
            vertex.textureCoordinates.x *= width;
            vertex.textureCoordinates.y *= height;

            // int tilesPerRow = 9;
            // int tilesPerColumn = 10;
            // int tileIndex = 3;  // which tile you want

            // // Calculate which grid cell
            // int tileX = tileIndex % tilesPerRow;
            // int tileY = tileIndex / tilesPerRow;

            // // Convert to normalized coordinates (0-1 range)
            // float tileWidth = 1.0f / tilesPerRow;
            // float tileHeight = 1.0f / tilesPerColumn;

            // vertex.textureCoordinates.x = (tileX + vertex.textureCoordinates.x) * tileWidth;
            // vertex.textureCoordinates.y = (tileY + vertex.textureCoordinates.y ) * tileHeight;
            // vertex.textureCoordinates.x = 1 / (1 % 9);
            // vertex.textureCoordinates.y = 1 / (1 / 10);
            vertices.push_back(vertex);
        }
    }
}

std::unique_ptr<Mesh> Chunk::toMesh(WorldManager &worldManager){
    // auto t1 = std::chrono::high_resolution_clock::now();
    std::vector<Vertex> vertices;
    for (unsigned int face = 0; face < 6 ; face++){
        unsigned int layerAxis= 0, planeAxis1= 0, planeAxis2 = 0;
        if (face < 2){
            layerAxis = 2;
            planeAxis1 = 1;
            planeAxis2 = 0;
        }
        else if (face < 4) {
            layerAxis = 1;
            planeAxis1 = 0;
            planeAxis2 = 2;
        }
        else {
            layerAxis = 0;
            planeAxis1 = 1;
            planeAxis2 = 2;
        }
        std::array<int, 3> coords;
       
        for ( unsigned int layer = 0; layer < CHUNK_SIZE ; layer++){
            std::array<int, CHUNK_SIZE> line;
            std::array<std::array<int, CHUNK_SIZE> , CHUNK_SIZE> plane;
            line.fill(-1);
            plane.fill(line);
            for (unsigned int i = 0; i < CHUNK_SIZE ; i++){  
                for ( unsigned int j = 0; j < CHUNK_SIZE; j++){
                    coords[layerAxis] = layer;
                    coords[planeAxis1] = i;
                    coords[planeAxis2] = j;

                    if ( getBlockAt(coords[0], coords[1], coords[2]) == AIR)
                        continue;
                    plane[i][j] = occlusionCulling(layerAxis,coords, face, worldManager);
                }
            }
    
            for (int y = 0; y < CHUNK_SIZE; y++) {
                for (int x = 0; x < CHUNK_SIZE; x++) {
                    if (plane[y][x] == AIR)
                        continue;
                    int id = plane[y][x];
                    int width = 1;
                    while (x + width < CHUNK_SIZE &&
                        plane[y][x + width] == id) {
                        width++;
                    }
                    int height = 1;
                    bool done = false;
                    while (y + height < CHUNK_SIZE && !done) {
                        for (int k = 0; k < width; k++) {
                            if (plane[y + height][x + k] != id) {
                                done = true;
                                break;
                            }
                        }
                        if (!done) height++;
                    }
                    buildTriangles(vertices,face, layer, x, y, height, width);
                    for (int dy = 0; dy < height; dy++) {
                        for (int dx = 0; dx < width; dx++) {
                            plane[y + dy][x + dx] = AIR;
                        }
                    } 
                }
            }
        }

    }
    // auto t2 = std::chrono::high_resolution_clock::now();
    // auto cpu_time = std::chrono::duration<double, std::milli>(t2 - t1).count();
    // std::cout << "CPU: " << cpu_time << "ms\n";
    return std::make_unique<Mesh>(vertices);
}

Chunk::~Chunk()
{
}
