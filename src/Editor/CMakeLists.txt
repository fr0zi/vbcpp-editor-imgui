set (EDITOR_SOURCES 
    src/Editor/MainMenu.cpp
)

set (EDITOR_HEADERS 
    src/Editor/MainMenu.h
    src/Editor/Editor.h
)

#source_group("ImGui" FILES ${GUI_SOURCES} ${GUI_HEADERS})

set (EDITOR_SOURCES ${EDITOR_SOURCES} PARENT_SCOPE)
set (EDITOR_HEADERS ${EDITOR_HEADERS} PARENT_SCOPE)