set (SCENE_SOURCES
    src/Scene/Transform.cpp
    src/Scene/SceneObject.cpp
    src/Scene/CameraStatic.cpp
    src/Scene/CameraFPS.cpp
)

set (SCENE_HEADERS
    src/Scene/Transform.h
    src/Scene/SceneObject.h
    src/Scene/CameraStatic.h
    src/Scene/CameraFPS.h
)

set (SCENE_SOURCES ${SCENE_SOURCES} PARENT_SCOPE)
set (SCENE_HEADERS ${SCENE_HEADERS} PARENT_SCOPE)