set (GRAPHICS_SOURCES 
    src/Graphics/LoadShader.cpp
    src/Graphics/Image.cpp
    src/Graphics/Texture2D.cpp
    src/Graphics/Renderer.cpp
)

set (GRAPHICS_HEADERS 
    src/Graphics/LoadShader.h
    src/Graphics/Image.h
    src/Graphics/Texture2D.cpp
    src/Graphics/stb_image.h
    src/Graphics/Vertex.h
    src/Graphics/Cube.hpp
    src/Graphics/Renderer.h
)

set (GRAPHICS_SOURCES ${GRAPHICS_SOURCES} PARENT_SCOPE)
set (GRAPHICS_HEADERS ${GRAPHICS_HEADERS} PARENT_SCOPE)