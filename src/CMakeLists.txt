# Define the executable target for our engine
add_executable(engine
    main.cpp
    core/Vector3.cpp
    core/Matrix4.cpp
    core/Matter.cpp
    core/TransformLaw.cpp
    core/MaterialColorLaw.cpp
    renderer/Camera.cpp
    renderer/Mesh.cpp
    renderer/Material.cpp
    renderer/Renderer.cpp
    renderer/Window.cpp
    editor/Editor.cpp
    ../vendor/imgui.cpp
    ../vendor/imgui_demo.cpp
    ../vendor/imgui_draw.cpp
    ../vendor/imgui_widgets.cpp
    ../vendor/imgui_tables.cpp
    ../vendor/imgui_impl_sdl3.cpp
    ../vendor/imgui_impl_opengl3.cpp
    ../Glad/src/glad.c
)

# Define the include directories for the engine target
target_include_directories(engine PUBLIC
    .
    ../vendor
    ../Glad/include
)

# Find the OpenGL package
find_package(OpenGL REQUIRED)

# Link the engine against SDL3 and OpenGL
target_link_libraries(engine PRIVATE SDL3::SDL3 OpenGL::GL)
