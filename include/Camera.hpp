#pragma once 
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <array>

#define SPEED 5
class Camera
{
private:
    glm::vec3 _position;
    float _fov ;
    float _aspect ;
    float _near ;
    float _far ;

    glm::vec3 _worldUp;

    glm::vec3 _localFront;
    glm::vec3 _localRight;
    glm::vec3 _localUp;

    float lastX;
    float lastY;

public:
    Camera(const glm::vec3 &position, float fov = 80, float aspect = 2, float near = 0.1, float far = 100);
    ~Camera();

    void setPosition(const glm::vec3 &position);
    glm::vec3 &getPosition();
    const glm::vec3 &getPosition() const;
    void updatePosition();
    void updateRotation();

    const glm::mat4 getViewMatrix() const ;
    const glm::mat4 getProjectionMatrix() const ;
    float _yaw;
    float _pitch;
    void setNewCursorPosition(float newX, float newY);
    std::array<float, 3> moveFlags{};
};

Camera::Camera(const glm::vec3 &position, float fov , float aspect, float near, float far): _position(position), _fov(fov), _aspect(aspect), _near(near), _far(far) {
    _worldUp = {0, 1, 0};
    _yaw = -90;
    _pitch = 0;

    lastX = 0;
    lastY = 0;

    updateRotation();
}

void Camera::setNewCursorPosition(float newX, float newY){

    if (!lastX && !lastY){
        lastX = newX;
        lastY = newY;
        return;
    }
    float dX = newX - lastX;
    float dY = lastY - newY;

    lastX = newX;
    lastY = newY;
    _yaw += dX  * 0.1;
    _pitch += dY * 0.1;
}


void Camera::setPosition(const glm::vec3 &position){
    _position = position;
}


void Camera::updatePosition(){
    _position += _localRight * (moveFlags[0] * SPEED);
    _position += _worldUp * (moveFlags[1] * SPEED);
    _position += _localFront * (moveFlags[2] * SPEED);
}

glm::vec3 &Camera::getPosition(){
    return _position;
}

const glm::vec3 &Camera::getPosition() const{
    return _position;
}


void Camera::updateRotation(){
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
