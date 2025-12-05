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
    Camera(const glm::vec3 &position, float fov = 80, float aspect = 1920/1080, float near = 0.1, float far = 1000);
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
    std::array<int, 3> getPositionArray();
};
