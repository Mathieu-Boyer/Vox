#pragma once

#include <vector>
#include "Mesh.hpp"
#include "Texture.hpp"
#include "Transform.hpp"
class Renderable
{
private:
    const Mesh &_mesh;
    const Texture *_texture;

public:
    Renderable(Mesh &mesh, const Texture *texture);
    ~Renderable();
    void draw();
    Transform transform;
};