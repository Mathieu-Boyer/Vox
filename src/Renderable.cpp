#include "Renderable.hpp"



Renderable::Renderable(Mesh &mesh, const Texture *texture) : _mesh(mesh), _texture(texture){
}

void Renderable::draw(){
    if (_texture)
        _texture->bind();
    // for (unsigned int i = 0 ; i <  _meshes.size() ; i++)
        // _meshes[i].draw();
    _mesh.draw();
}

Renderable::~Renderable()
{
}
