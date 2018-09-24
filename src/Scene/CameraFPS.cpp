#include "CameraFPS.h"

CameraFPS::CameraFPS(glm::vec2 screenSize)
: CameraStatic(screenSize),
  _movementSpeed(1.0f), _rotationSpeed(0.2f),
  _yaw(-90.0f), _pitch(0.0f)
{
    updateCameraVectors();
}

CameraFPS::~CameraFPS()
{

}

void CameraFPS::rotateFromMouse(double posX, double posY)
{
    posX *= _rotationSpeed;
    posY *= _rotationSpeed;

    _yaw   += posX;
    _pitch -= posY;

    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    if (_pitch > 89.0f)
        _pitch = 89.0f;
    if (_pitch < -89.0f)
        _pitch = -89.0f;

    updateCameraVectors();
}

void CameraFPS::move(MovementDirection direction, double deltaTime)
{
    float velocity = _movementSpeed * deltaTime;
    switch (direction)
    {
        case FORWARD:
            _transform.getPositionRef() += _cameraFront * velocity;
        break;

        case BACKWARD:
            _transform.getPositionRef() -= _cameraFront * velocity;
        break;

        case STRAFE_LEFT:
            _transform.getPositionRef() -= _cameraRight * velocity;
        break;

        case STRAFE_RIGHT:
            _transform.getPositionRef() += _cameraRight * velocity;
        break;
    }
}

const float CameraFPS::getMovementSpeed() const
{
    return _movementSpeed;
}

const float CameraFPS::getRotationSpeed() const
{
    return _rotationSpeed;
}

void CameraFPS::setMovementSpeed(const float speed)
{
    _movementSpeed = speed;
}

void CameraFPS::setRotationSpeed(const float speed)
{
    _rotationSpeed = speed;
}


void CameraFPS::updateCameraVectors()
{
    glm::vec3 front;

    front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    front.y = sin(glm::radians(_pitch));
    front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    
    _cameraFront = glm::normalize(front);
    // Also re-calculate the Right and Up vector
    _cameraRight = glm::normalize(glm::cross(_cameraFront, glm::vec3(0.0, 1.0f, 0.0f)));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    _cameraUp    = glm::normalize(glm::cross(_cameraRight, _cameraFront));
}

void CameraFPS::updateCameraViewProjection()
{
    _cameraView =  glm::lookAt(
        _transform.getPositionRef(),    // the position of your camera, in world space
        _transform.getPositionRef() + _cameraFront,   // where you want to look at, in world space
        glm::vec3(0.0f, 1.0f, 0.0f)        // probably glm::vec3(0,1,0), but (0,-1,0) would make you looking upside-down, which can be great too
    );

    _cameraProjection =  glm::perspective(
        glm::radians(46.0f), // The vertical Field of View, in radians: the amount of "zoom". Think "camera lens". Usually between 90° (extra wide) and 30° (quite zoomed in)
        _screenSize.x / _screenSize.y,       // Aspect Ratio. Depends on the size of your window. Notice that 4/3 == 800/600 == 1280/960, sounds familiar ?
        0.1f,              // Near clipping plane. Keep as big as possible, or you'll get precision issues.
        1000.0f             // Far clipping plane. Keep as little as possible.
    );
}