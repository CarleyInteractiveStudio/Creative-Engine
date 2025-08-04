#pragma once

#include "Engine/Core/Memory.h"
#include "Engine/MatterSystem/Matter.h"

#include <vector>
#include <string>

namespace Creative {

// SceneSpace is a container for all the active Matter in a scene.
// It is responsible for creating, destroying, and updating all the Matter.
class SceneSpace
{
public:
    SceneSpace();
    ~SceneSpace();

    // Creates a new Matter object, adds it to the scene, and returns a raw pointer to it.
    // The SceneSpace retains ownership of the Matter.
    Matter* CreateMatter(const std::string& name = "Matter");

    // Schedules a Matter object for destruction at the end of the frame.
    void DestroyMatter(Matter* matter);

    // Called every frame by the main application loop.
    void Update(float deltaTime);

public:
    // Returns a const reference to the list of Matter objects.
    const std::vector<Scope<Matter>>& GetMatters() const { return m_Matters; }

private:
    // This vector owns all the Matter objects in the scene.
    std::vector<Scope<Matter>> m_Matters;
};

} // namespace Creative
