#pragma once 
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera
{
private:
    glm::vec3 _position;
    float _fov ;
    float _aspect ;
    float _near ;
    float _far ;

    glm::vec3 _worldUp;
    float _yaw;
    float _pitch;

    glm::vec3 _localFront;
    glm::vec3 _localRight;
    glm::vec3 _localUp;

    void updateCamera();
public:
    Camera(const glm::vec3 &position, float fov = 80, float aspect = 1.0, float near = 0.1, float far = 100);
    ~Camera();


    const glm::mat4 getViewMatrix() const ;
    const glm::mat4 getProjectionMatrix() const ;
};

Camera::Camera(const glm::vec3 &position, float fov , float aspect, float near, float far): _position(position), _fov(fov), _aspect(aspect), _near(near), _far(far) {
    _worldUp = {0, 1, 0};
    _yaw = -90;
    _pitch = 0;
}

void Camera::updateCamera(){
    _localFront = glm::normalize((glm::vec3){
        cos(glm::radians(_pitch)) * cos(glm::radians(_yaw)),
        sin(glm::radians(_pitch)),
        cos(glm::radians(_pitch)) * sin(glm::radians(_yaw)),
    });
    _localRight = glm::normalize(glm::cross(_localFront, _worldUp));
    _localUp = glm::normalize(glm::cross(_localRight, _localFront));
}

const glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(_position, _position + _localFront, _localUp);
}

const glm::mat4 Camera::getProjectionMatrix() const {
    return glm::perspective(glm::radians(_fov), _aspect, _near, _far);
}


Camera::~Camera()
{
}
