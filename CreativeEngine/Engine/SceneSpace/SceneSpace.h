#pragma once

#include "Engine/Core/Memory.h"
#include "Engine/MatterSystem/Matter.h"

#include <vector>
#include <string>
#include <type_traits> // For std::is_base_of

namespace Creative {

// SceneSpace is a container for all the active Matter in a scene.
// It is responsible for creating, destroying, and updating all the Matter.
class SceneSpace
{
public:
    SceneSpace();
    ~SceneSpace();

    // Creates a new Matter object of a specific type T, adds it to the scene,
    // and returns a raw pointer to it. T must be a subclass of Matter.
    template<typename T>
    T* CreateMatter(const std::string& name = "Matter");

    // Schedules a Matter object for destruction at the end of the frame.
    void DestroyMatter(Matter* matter);

    // Called every frame by the main application loop.
    void Update(float deltaTime);

    // Returns a const reference to the list of Matter objects.
    const std::vector<Scope<Matter>>& GetMatters() const { return m_Matters; }

private:
    // This vector owns all the Matter objects in the scene.
    std::vector<Scope<Matter>> m_Matters;
};

// --- Template Implementation ---

template<typename T>
T* SceneSpace::CreateMatter(const std::string& name)
{
    // This ensures at compile-time that we can only create things that are Matter.
    static_assert(std::is_base_of<Matter, T>::value, "T must be a derivative of Matter");

    // Create the new Matter object.
    Scope<T> newMatter = CreateScope<T>(name);
    T* rawPtr = newMatter.get();

    // Add it to our list, transferring ownership.
    m_Matters.push_back(std::move(newMatter));

    return rawPtr;
}

} // namespace Creative
