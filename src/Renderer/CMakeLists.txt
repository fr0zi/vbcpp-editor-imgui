set (RENDERER_SOURCES 
    src/Renderer/LoadShader.cpp
    src/Renderer/VBImage.cpp
)

set (RENDERER_HEADERS 
    src/Renderer/LoadShader.h
    src/Renderer/VBImage.h
    src/Renderer/stb_image.h
    src/Renderer/Vertex.h
    src/Renderer/Cube.hpp
)

set (RENDERER_SOURCES ${RENDERER_SOURCES} PARENT_SCOPE)
set (RENDERER_HEADERS ${RENDERER_HEADERS} PARENT_SCOPE)