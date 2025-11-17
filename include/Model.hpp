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

std::vector<Mesh> &Model::getMeshes(){
    return meshes;
}
const std::vector<Mesh> &Model::getMeshes() const{
    return meshes;
}

Model::Model(const std::string &modelPath)
{

    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(modelPath.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        throw std::runtime_error("Error while loading the model");

    processNode(scene, scene->mRootNode);
}

void Model::processNode(const aiScene *scene, aiNode *node){
    for (unsigned i = 0; i < node->mNumMeshes ; i++){
        int meshIndex = node->mMeshes[i];
        aiMesh *mesh = scene->mMeshes[meshIndex];
        meshes.push_back(createMesh(mesh));
    }
    for (unsigned i = 0 ; i < node->mNumChildren; i++)
        processNode(scene, node->mChildren[i]);
}

Mesh Model::createMesh(aiMesh *mesh){

    std::vector<Vertex> vertices;
    for (unsigned int i = 0 ; i < mesh->mNumVertices; i++){
        Vertex vertex;
        vertex.position.x = mesh->mVertices[i].x;
        vertex.position.y = mesh->mVertices[i].y;
        vertex.position.z = mesh->mVertices[i].z;
        aiVector3D *texCoor  = mesh->mTextureCoords[0];

        if (texCoor){
            vertex.textureCoordinates.x = texCoor[i].x;
            vertex.textureCoordinates.y = texCoor[i].y;
        }
        else
            vertex.textureCoordinates = {0, 0}; // or maybe i'll add box wrapping idk yet

        vertex.normal.x = mesh->mNormals[i].x;
        vertex.normal.y = mesh->mNormals[i].y;
        vertex.normal.z = mesh->mNormals[i].z;

        vertices.push_back(vertex);
    }
    return Mesh(vertices);
}


Model::~Model()
{
}
