cmake_minimum_required(VERSION 3.6)

project(VBCPPEditor)

set(BIN_NAME vbcpp_editor)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_subdirectory(libs/glew)
add_subdirectory(libs/glfw)
#add_subdirectory(libs/glm)

add_subdirectory(src/ImGui)
source_group("ImGui" FILES ${GUI_SOURCES} ${GUI_HEADERS})

add_subdirectory(src/Renderer)
source_group("Renderer" FILES ${RENDERER_SOURCES} ${RENDERER_HEADERS})

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
                    ${GUI_SOURCES} 
                    ${GUI_HEADERS}
                    ${WINDOW_SOURCES}
                    ${WINDOW_HEADERS}
                    ${RENDERER_SOURCES}
                    ${RENDERER_HEADERS}
                    ${SCENE_SOURCES}
                    ${SCENE_HEADERS}
                    ${SOURCES}
)

#add_custom_command(TARGET ${BIN_NAME} PRE_BUILD
#                   COMMAND ${CMAKE_COMMAND} -E copy_folder
#                       ${CMAKE_SOURCE_DIR}/Data ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Data)

set_target_properties (${BIN_NAME} PROPERTIES VS_STARTUP_PROJECT ${BIN_NAME})

target_link_libraries(${BIN_NAME} glfw glew)

file(COPY ${CMAKE_SOURCE_DIR}/Data DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
