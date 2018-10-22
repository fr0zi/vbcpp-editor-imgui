#include "CameraStatic.h"

CameraStatic::CameraStatic(glm::vec2 screenSize)
  : _screenSize(screenSize)
{

}

CameraStatic::~CameraStatic()
{

}

scene::Transform& CameraStatic::getTransform()
{
    return _transform;
}

void CameraStatic::setTransform(const scene::Transform transform)
{
    _transform = transform;
}

void CameraStatic::setLookAt(const glm::vec3 lookAt)
{
    _lookAt = lookAt;
}

void CameraStatic::setScreenSize(int width, int height)
{
    _screenSize = glm::vec2(width, height);
}

const glm::vec3 CameraStatic::getLookAt() const
{
    return _lookAt;
}

glm::mat4& CameraStatic::getViewMatrix()
{
    updateCameraViewProjection();

    return _cameraView;
}

glm::mat4& CameraStatic::getProjectionMatrix()
{
    updateCameraViewProjection();

    return _cameraProjection;
}


void CameraStatic::updateCameraViewProjection()
{
    _cameraView =  glm::lookAt(
        _transform.getPositionRef(),    // the position of your camera, in world space
        _lookAt,   // where you want to look at, in world space
        glm::vec3(0.0f, 1.0f, 0.0f)        // probably glm::vec3(0,1,0), but (0,-1,0) would make you looking upside-down, which can be great too
    );

    _cameraProjection =  glm::perspective(
        glm::radians(46.0f), // The vertical Field of View, in radians: the amount of "zoom". Think "camera lens". Usually between 90° (extra wide) and 30° (quite zoomed in)
        _screenSize.x / _screenSize.y,       // Aspect Ratio. Depends on the size of your window. Notice that 4/3 == 800/600 == 1280/960, sounds familiar ?
        0.1f,              // Near clipping plane. Keep as big as possible, or you'll get precision issues.
        1000.0f             // Far clipping plane. Keep as little as possible.
    );
}