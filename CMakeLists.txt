cmake_minimum_required(VERSION 3.6)

project(VBCPPEditor)

set(BIN_NAME vbcpp_editor)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_subdirectory(libs/glew)
add_subdirectory(libs/glfw)


add_subdirectory(src/ImGui)
source_group("ImGui" FILES ${IMGUI_SOURCES} ${IMGUI_HEADERS})

add_subdirectory(src/Core)
source_group("Core" FILES ${CORE_SOURCES} ${CORE_HEADERS})

add_subdirectory(src/Editor)
source_group("GUI" FILES ${EDITOR_SOURCES} ${EDITOR_HEADERS})

add_subdirectory(src/Graphics)
source_group("Graphics" FILES ${GRAPHICS_SOURCES} ${GRAPHICS_HEADERS})

add_subdirectory(src/Scene)
source_group("Scene" FILES ${SCENE_SOURCES} ${SCENE_HEADERS})

set (WINDOW_SOURCES
    src/Window/Window.cpp
)

set (WINDOW_HEADERS
    src/Window/Window.h
)

source_group("Window" FILES ${WINDOW_SOURCES} ${WINDOW_HEADERS})

set (SOURCES 
    src/main.cpp
)

source_group("MapEditor" FILES ${SOURCES})

find_library(glew glew32 PATHS lib)
include_directories (libs/glew/include)

find_library(glfw glfw3 PATHS lib)
include_directories (libs/glfw/include)

include_directories (libs/glm/include)

add_executable(${BIN_NAME}
                    ${IMGUI_SOURCES}
                    ${IMGUI_HEADERS}
                    ${CORE_SOURCES}
                    ${CORE_HEADERS}
                    ${GUI_SOURCES} 
                    ${GUI_HEADERS}
                    ${WINDOW_SOURCES}
                    ${WINDOW_HEADERS}
                    ${GRAPHICS_SOURCES}
                    ${GRAPHICS_HEADERS}
                    ${SCENE_SOURCES}
                    ${SCENE_HEADERS}
                    ${SOURCES}
)

set_target_properties (${BIN_NAME} PROPERTIES VS_STARTUP_PROJECT ${BIN_NAME})

target_link_libraries(${BIN_NAME} glfw glew)

file(COPY ${CMAKE_SOURCE_DIR}/Data DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
