# Creative Engine

This is a 3D game engine written in C++. It is still under development.

## Vision and Architecture

### Core Concept: Matter and Laws

In Creative Engine, everything in the world is **Matter**, and every **Matter** operates according to one or more **Laws**.

-   **Matter**: An object or entity in the world (tangible or intangible). This is similar to a `GameObject` in Unity.
-   **Law**: A rule or module that defines the behavior of that **Matter** (e.g., its movement, appearance, sound, etc.). This is similar to a `Component` in Unity.

### Engine Layers

Creative Engine will be divided into layers that work together but are modular:

*   **Platform Layer:** Windows, input (keyboard, mouse, gamepad), timing, threads. Abstraction of the operating system.
*   **Core Layer:** Math, memory, logging, global events. Time system (delta time, frames).
*   **Matter and Law System:** Registration and management of all **Matter**. Administration of **Laws** and how they are applied. Hierarchy (parent/child) and propagation of transformations.
*   **Scene Space:** Container of all active **Matter**. Support for sub-scenes and streaming of parts of the world.
*   **Rendering (2D and 3D):** Cameras, materials, lights, meshes. Optimized graphics pipeline.
*   **Physics:** Collision and simulation engine. **Laws** that apply movement, gravity, forces.
*   **Animation:** Skeletal and sprite animations. Mixing of clips and transitions.
*   **Audio:** Positional sound, music, effects.
*   **Scripting (C#):** API for the user to control **Matter** and **Laws** from scripts. Lifecycle (`Start`, `Update`, `OnEvent`).
*   **Asset Management:** Import of models (FBX, glTF), textures, sounds. Conversion to internal format.
*   **Editor Tools:** Graphical interface to create, move, and modify **Matter** and **Laws**. Inspector and scene view.
*   **Build System:** Packaging of assets and final compilation.

### Conceptual Folder Structure

```
/CreativeEngine/
  /Engine/
    /Platform/        # Platform and input
    /Core/            # Engine core
    /MatterSystem/    # Management of Matter and Laws
    /SceneSpace/      # Scenes and sub-scenes
    /Renderer/        # 2D/3D Render
    /Physics/         # Physics and collisions
    /Animation/       # Animations
    /Audio/           # Sound
    /Scripting/       # C# support
    /Assets/          # Asset manager
    /UI/              # Editor tools
  /Editor/            # Visual editor
  /Tools/             # CLI tools
  /GameProjects/      # Projects made with the engine
  /Build/             # Build system
  /Docs/              # Documentation
```

### Clear Development Instructions

#### Phase 0 — Fundamentals

*   Define own file formats for:
    *   Scenes (`.cescene`) → list of **Matter** and their **Laws**.
    *   Prefabs (`.ceprefab`) → templates of **Matter** with **Laws**.
    *   Asset bundles (`.cepack`) → resource packaging.
*   Create the base engine:
    *   Initialize platform, input, and timer.
    *   Core configuration.
    *   Empty but functional asset manager.

#### Phase 1 — Matter and Laws

*   Design **Matter**:
    *   Unique identifier, name, and state (active/inactive).
    *   List of applied **Laws**.
    *   Hierarchy (parent/child).
*   Design **Laws**:
    *   Each **Law** has its own type and data.
    *   Examples: `MotionLaw`, `MaterialColorLaw`, `PhysicsLaw`, `AudioLaw`.
    *   They can interact with each other via an event system.
*   Create **Scene Space**:
    *   Container of active **Matter**.
    *   Support for loading and unloading scenes without restarting everything.

#### Phase 2 — Rendering

*   Support for:
    *   Orthographic (2D) and perspective (3D) camera.
    *   Rendering of meshes and sprites.
    *   Basic lighting.
*   Integrate appearance laws (`MaterialColorLaw`) that handle:
    *   Materials, textures, colors.
    *   FBX/glTF models converted to internal format.

#### Phase 3 — Physics and Animation

*   **Physics:**
    *   `PhysicsLaw` for movement and collisions.
    *   Detection and response engine.
*   **Animation:**
    *   `AnimationLaw` to play clips.
    *   Support for skeletal animations and blending.

#### Phase 4 — Scripting and Editor

*   Integrate C#:
    *   Exposed API to manipulate **Matter** and **Laws**.
    *   Hooks (`Start`, `Update`, `OnCollision`, etc.).
*   **Editor:**
    *   Scene view and **Matter** hierarchy.
    *   Inspector to edit **Laws** and properties.
    *   Drag and drop assets.

#### Phase 5 — Build and Optimization

*   **Packaging:**
    *   Asset bundles (`.cepack`) with all optimized resources.
    *   Script compilation.
*   **Optimization:**
    *   Culling, batching, LOD.
    *   Scene streaming.

## Current Status

The project has been migrated to SDL3, but the executable currently crashes at runtime with the following error:

```
engine: vendor/imgui.cpp:8534: void ImGui::End(): Assertion `(g.CurrentWindowStack.Size > 1) && "Calling End() too many times!"' failed.
```

This error is related to the ImGui library and seems to be caused by an incorrect number of calls to `ImGui::Begin()` and `ImGui::End()`. I have been unable to resolve this issue, but I have left the UI code in a simplified state to make it easier to debug.

## Current State

The engine is currently in **Phase 1**. We have laid the foundations and implemented the core `Matter` and `Law` system.

### Features Implemented:

*   **Platform Layer:** Window creation, input handling (keyboard, mouse), and timing using SDL2.
*   **Core System:** Basic math classes (`Vector3`, `Matrix4`), and the `Matter` and `Law` system.
*   **Initial Laws:**
    *   `TransformLaw`: Manages the position, rotation, and scale of a `Matter` object.
    *   `MaterialColorLaw`: Manages the color of a `Matter` object.
*   **Renderer:** A basic renderer that can draw `Matter` objects based on their `TransformLaw` and `MaterialColorLaw`.
*   **Editor:** An integrated editor using ImGui that allows you to inspect and modify the properties of `Matter` and its `Laws`.

## How to Contribute

The engine is designed to be easily extensible. To create a new `Law`, you can follow these steps:

1.  Create a new class that inherits from `Creative::Law`.
2.  Implement the `OnUpdate(float dt)` method to define the behavior of the law.
3.  Add any properties that the law needs.
4.  Add the new law to a `Matter` object using `matter->AddLaw<YourNewLaw>();`.

## Getting Started

To get started, you will need to have the following installed:

*   A C++ compiler (g++) that supports C++14.
*   Make
*   SDL2

Once you have these installed, you can build the engine for Linux by running the following command:

```
make
```

### Building for Windows (Cross-compilation from Linux)

To build the engine for Windows from a Linux environment, you will need to have the following installed:

*   **MinGW-w64:** A cross-compiler that allows you to create Windows executables from Linux. You can install it on Debian/Ubuntu with `sudo apt-get install mingw-w64`.
*   **SDL2 Development Libraries for MinGW:** You need to download the development libraries for MinGW from the SDL2 website and place them in a location of your choice.

Once you have these installed, you will need to edit the `Makefile` and update the following variables with the correct paths to your SDL2 libraries:

*   `WIN_CXXFLAGS`: Update the `-I` flag to point to the `include` directory of your SDL2 libraries.
*   `WIN_LDFLAGS`: Update the `-L` flag to point to the `lib` directory of your SDL2 libraries.

After updating the `Makefile`, you can build the Windows executable by running the following command:

```
make windows
```

## Usage

To run the engine, you can run the following command:

```
./engine
```

This will open a window with the editor, where you can see and interact with a sample `Matter` object.
