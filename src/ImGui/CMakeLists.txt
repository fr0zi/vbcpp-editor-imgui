set (IMGUI_SOURCES 
    src/ImGui/imgui.cpp
    src/ImGui/imgui_demo.cpp
    src/ImGui/imgui_draw.cpp
    src/ImGui/imgui_impl_glfw_gl3.cpp
    src/ImGui/ImguiWindowsFileIO.cpp
)

set (IMGUI_HEADERS 
    src/ImGui/imgui.h
    src/ImGui/imconfig.h
    src/ImGui/imgui_impl_glfw_gl3.h
    src/ImGui/imgui_internal.h
    src/ImGui/stb_rect_pack.h
    src/ImGui/stb_textedit.h
    src/ImGui/stb_truetype.h
    src/ImGui/ImguiWindowsFileIO.hpp
)

#source_group("ImGui" FILES ${GUI_SOURCES} ${GUI_HEADERS})

set (IMGUI_SOURCES ${IMGUI_SOURCES} PARENT_SCOPE)
set (IMGUI_HEADERS ${IMGUI_HEADERS} PARENT_SCOPE)