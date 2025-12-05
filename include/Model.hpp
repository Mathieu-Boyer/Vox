#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.hpp"

class Model
{
private:
    /* data */
    std::vector<Mesh> meshes;

    void processNode(const aiScene *scene, aiNode *node);
public:

    Mesh createMesh(aiMesh *mesh);
    Model(const std::string &modelPath);
    ~Model();

    std::vector<Mesh> &getMeshes();
    const std::vector<Mesh> &getMeshes() const;
};