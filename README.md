# Creative Engine

This is a 3D game engine written in C++. It is still under development.

## Vision and Architecture

### Core Concept: Matter and Laws

In Creative Engine, everything in the world is **Matter**, and every **Matter** operates according to one or more **Laws**.

-   **Matter**: An object or entity in the world (tangible or intangible). This is similar to a `GameObject` in Unity.
-   **Law**: A rule or module that defines the behavior of that **Matter** (e.g., its movement, appearance, sound, etc.). This is similar to a `Component` in Unity.

## Current State

The engine is currently in **Phase 1**, with a focus on building out the core editor functionality. We have a foundational editor built with ImGui and a cross-platform CMake build system.

### Features Implemented:

*   **Build System:** Cross-platform build system using CMake.
*   **Platform Layer:** Window creation and input handling using SDL3.
*   **Core System:** Basic math classes (`Vector3`, `Matrix4`), and the `Matter` and `Law` system.
*   **Editor:** An integrated editor using ImGui with the following panels:
    *   **Scene View:** A visual representation of the scene, rendered via a framebuffer.
    *   **Hierarchy:** Lists all `Matter` objects in the scene and allows for selection.
    *   **Inspector:** Displays and allows editing of properties for selected `Matter` objects and their attached `Laws`. Includes an "Add Law" feature.
    *   **Assets:** Lists files and folders in the project directory and allows for the creation of new ones.
*   **Initial Laws:**
    *   `TransformLaw`: Manages the position, rotation, and scale of a `Matter` object.
    *   `MaterialColorLaw`: Manages the color of a `Matter` object.

## Roadmap

Here are some of the planned features for the future development of the editor:

### Scene View Gizmos

A crucial feature for a 3D editor is the ability to manipulate objects directly in the scene view. The plan is to implement a fully-featured gizmo with the following capabilities:

*   **Operations Toolbar:** A small toolbar in the editor to switch between Translate, Rotate, and Scale modes.
*   **Translate Gizmo:** A gizmo with 3 colored arrows (red, green, blue) to move objects along the X, Y, and Z axes.
*   **Rotate Gizmo:** A gizmo with 3 colored rings to rotate objects around the X, Y, and Z axes.
*   **Scale Gizmo:** A gizmo with handles to scale objects along the axes, as well as a central handle for uniform scaling.

**Implementation Note:** The recommended approach for this feature is to integrate the **ImGuizmo** library (`github.com/CedricGuillemet/ImGuizmo`), which is a popular and robust solution that works directly with ImGui.

## Getting Started

The project is built using CMake, which can generate project files for a variety of compilers and IDEs.

### Prerequisites

*   **CMake:** Version 3.16 or higher.
*   **A C++17 compatible compiler:** (e.g., GCC, Clang, MSVC).
*   **(For Windows):** Visual Studio 2019 or later with the "Desktop development with C++" workload.

### Building on Linux

```bash
# From the project root directory
mkdir build
cd build
cmake ..
make
```
The executable will be located at `build/src/engine`.

### Building on Windows

```bash
# From the project root directory, in a command prompt
mkdir build
cd build
cmake ..
```
This will generate a Visual Studio solution file (`CreativeEngine.sln`) inside the `build` directory. Open this file in Visual Studio to compile and run the project.
