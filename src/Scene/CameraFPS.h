#pragma once

#include "CameraStatic.h"

enum MovementDirection {
    FORWARD,
    BACKWARD,
    STRAFE_LEFT,
    STRAFE_RIGHT
};

// Camera position and rotation calculations got from https://learnopengl.com/Getting-started/Camera

class CameraFPS : virtual public CameraStatic
{
    public:
        CameraFPS(glm::vec2 screenSize);
        virtual ~CameraFPS();

        void rotateFromMouse(float posX, float posY);
        void move(MovementDirection direction, double deltaTime);

    protected:
        glm::vec3 _cameraFront;
        glm::vec3 _cameraUp;
        glm::vec3 _cameraRight;

        float _movementSpeed;
        float _rotationSpeed;

        float _yaw;
        float _pitch;

        void updateCameraVectors();

        void updateCameraViewProjection() override;
};
