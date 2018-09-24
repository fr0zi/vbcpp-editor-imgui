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

        void rotateFromMouse(double posX, double posY);
        void move(MovementDirection direction, double deltaTime);

        const float getMovementSpeed() const;
        const float getRotationSpeed() const;

        void setMovementSpeed(const float speed);
        void setRotationSpeed(const float speed);

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
