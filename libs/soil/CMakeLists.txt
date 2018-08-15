cmake_minimum_required(VERSION 3.6)

project(SOIL)

set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set (SOIL_LIB_NAME soil)
set (DLL_PREFIX lib)

find_package (OpenGL REQUIRED)

set(SOURCES SOIL/image_helper.c
            SOIL/stb_image_aug.c
            SOIL/image_DXT.c
            SOIL/SOIL.c)

add_library(soil SHARED ${SOURCES})

set_target_properties (soil PROPERTIES OUTPUT_NAME "${SOIL_LIB_NAME}" PREFIX "${DLL_PREFIX}")
target_link_libraries (soil LINK_PUBLIC ${OPENGL_LIBRARIES})