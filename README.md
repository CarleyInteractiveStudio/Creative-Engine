# Creative Engine

This is a 3D game engine written in C++. It is still under development.

## Core Concept: Matter and Laws

In Creative Engine, everything in the world is **Matter**, and every **Matter** operates according to one or more **Laws**.

-   **Matter**: An object or entity in the world (tangible or intangible). This is similar to a `GameObject` in Unity.
-   **Law**: A rule or module that defines the behavior of that **Matter** (e.g., its movement, appearance, sound, etc.). This is similar to a `Component` in Unity.

## Current State

The engine is currently in an early stage of development. We have laid the foundations and implemented the core `Matter` and `Law` system.

### Features Implemented:

*   **Platform Layer:** Window creation, input handling (keyboard, mouse), and timing using SDL2.
*   **Core System:** Basic math classes (`Vector3`, `Matrix4`), and the `Matter` and `Law` system.
*   **Initial Laws:**
    *   `TransformLaw`: Manages the position, rotation, and scale of a `Matter` object.
    *   `AppearanceLaw`: Manages the color of a `Matter` object.
*   **Renderer:** A basic renderer that can draw `Matter` objects based on their `TransformLaw` and `AppearanceLaw`.
*   **Editor:** An integrated editor using ImGui that allows you to inspect and modify the properties of `Matter` and its `Laws`.

## Roadmap (Next Steps)

The following is a list of the next features to be implemented, based on the original plan:

*   **Physics:**
    *   `RigidbodyLaw` for movement and collisions.
    *   A collision detection and response engine.
*   **Animation:**
    *   `AnimationLaw` to play clips.
    *   Support for skeletal animations and blending.
*   **Scripting (C#):**
    *   An API to control `Matter` and `Laws` from scripts.
    *   Lifecycle hooks (`Start`, `Update`, `OnCollision`, etc.).
*   **Asset Management:**
    *   Importing models (FBX, glTF), textures, and sounds.
    *   Conversion to an internal format.
*   **Build System:**
    *   Packaging of assets and final compilation.

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

Once you have these installed, you can build the engine by running the following command:

```
make
```

## Usage

To run the engine, you can run the following command:

```
./engine
```

This will open a window with the editor, where you can see and interact with a sample `Matter` object.
