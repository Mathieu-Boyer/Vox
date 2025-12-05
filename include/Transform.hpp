#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Transform
{
private:
    /* data */
public:
    Transform(/* args */);

    glm::vec3 _translation;
    glm::vec3 _scale;
    glm::vec3 _rotation;


    glm::mat4 getModelMatrix();

    ~Transform();
};