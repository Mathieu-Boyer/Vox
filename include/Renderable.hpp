#pragma once

#include <vector>
#include "Mesh.hpp"
#include "Texture.hpp"
#include "Transform.hpp"
class Renderable
{
private:
    const std::vector<Mesh> &_meshes;
    const Texture *_texture;

public:
    Renderable(const std::vector<Mesh> &meshes, const Texture *texture);
    ~Renderable();
    void draw();
    Transform transform;
};

Renderable::Renderable(const std::vector<Mesh> &meshes, const Texture *texture) : _meshes(meshes), _texture(texture){
}

void Renderable::draw(){
    if (_texture)
        _texture->bind();
    for (unsigned int i = 0 ; i <  _meshes.size() ; i++)
        _meshes[i].draw();
}

Renderable::~Renderable()
{
}
