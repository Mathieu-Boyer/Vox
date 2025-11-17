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

Transform::Transform() : _translation({0,0,0}), _scale({1,1,1}), _rotation({0,0,0})
{

}

glm::mat4 Transform::getModelMatrix(){
    glm::mat4 model(1.0);

    model = glm::translate(model, _translation);
    model = glm::rotate(model, glm::radians(_rotation.x) , {1,0,0});
    model = glm::rotate(model, glm::radians(_rotation.y) , {0,1,0});
    model = glm::rotate(model, glm::radians(_rotation.z) , {0,0,1});
    model = glm::scale(model , _scale);

    return model;
}


Transform::~Transform()
{
}
