# Group source files
set(CORE_SOURCES
    core/Vector3.cpp
    core/Matrix4.cpp
    core/Matter.cpp
    core/TransformLaw.cpp
    core/MaterialColorLaw.cpp
)

set(RENDERER_SOURCES
    renderer/Camera.cpp
    renderer/Mesh.cpp
    renderer/Material.cpp
    renderer/Renderer.cpp
    renderer/Window.cpp
    renderer/Framebuffer.cpp
)

set(EDITOR_SOURCES
    editor/Editor.cpp
    editor/CameraController.cpp
    editor/Gizmo.cpp
)

set(VENDOR_SOURCES
    ../vendor/imgui.cpp
    ../vendor/imgui_demo.cpp
    ../vendor/imgui_draw.cpp
    ../vendor/imgui_widgets.cpp
    ../vendor/imgui_tables.cpp
    ../vendor/imgui_impl_sdl3.cpp
    ../vendor/imgui_impl_opengl3.cpp
    ../Glad/src/glad.c
)

# Define the executable target for our engine
add_executable(engine
    main.cpp
    ${CORE_SOURCES}
    ${RENDERER_SOURCES}
    ${EDITOR_SOURCES}
    ${VENDOR_SOURCES}
)

# Define the include directories for the engine target
target_include_directories(engine PUBLIC
    .
    ../vendor
    ../Glad/include
)

# Find the OpenGL package
find_package(OpenGL REQUIRED)

# Platform-specific configuration
if(WIN32)
    # On Windows, we need to link against SDL3main and some system libraries
    target_link_libraries(engine PRIVATE SDL3::SDL3 SDL3::SDL3main OpenGL::GL gdi32 shell32 user32)
    # This is a standard define for Windows GUI applications
    target_compile_definitions(engine PRIVATE WIN32)
else()
    # On other platforms (like Linux), this is sufficient
    target_link_libraries(engine PRIVATE SDL3::SDL3 OpenGL::GL)
endif()
