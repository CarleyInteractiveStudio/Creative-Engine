#pragma once

#include "Engine/MatterSystem/Matter.h"

namespace Creative {

// Camera2D is a specialized type of Matter that defines a viewpoint for the renderer.
// By inheriting from Matter, it can be placed in the SceneSpace and moved around
// just like any other game object.
class Camera2D : public Matter
{
public:
    // We pass the name up to the base Matter class constructor.
    Camera2D(std::string name = "Camera2D")
        : Matter(std::move(name))
    {}

    // The orthographic size determines the "zoom" level. A smaller size means
    // the camera is "zoomed in" more, showing a smaller area of the world.
    // This value represents the height of the view area in world units.
    float orthographicSize = 100.0f;

    // A simple flag to help the renderer find which camera to use.
    // A more robust system might have a camera manager or a tag system.
    bool isPrimary = true;
};

} // namespace Creative
