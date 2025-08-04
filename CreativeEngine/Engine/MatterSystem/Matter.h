#pragma once

#include "Engine/Core/Math.h"
#include "Engine/Core/Memory.h"
#include "Engine/MatterSystem/Law.h"
#include "Engine/Core/Log.h" // For logging in template methods

#include <vector>
#include <string>
#include <algorithm>

namespace Creative {

// Matter represents any object or entity in the game world.
// It is essentially a container for Laws and a Transform.
class Matter
{
public:
    Matter(std::string name = "Matter");
    virtual ~Matter();

    // This is called by SceneSpace each frame. It, in turn, calls Update on all its Laws.
    void Update(float deltaTime);

    // Adds a Law (component) of a specific type to this Matter.
    // Example: matter->AddLaw<MotionLaw>(5.0f);
    template<typename T, typename... Args>
    T* AddLaw(Args&&... args);

    // Gets the first Law of a specific type found on this Matter.
    // Returns nullptr if no Law of that type is found.
    template<typename T>
    T* GetLaw();

    // Removes the first Law of a specific type found on this Matter.
    template<typename T>
    void RemoveLaw();

    const std::string& GetName() const { return m_Name; }

    // --- Transform ---
    // Publicly accessible for simplicity. A more robust engine might make these
    // private and provide methods to manipulate them.
    Vec3 position = { 0.0f, 0.0f, 0.0f };
    Vec3 rotation = { 0.0f, 0.0f, 0.0f };
    Vec3 scale    = { 1.0f, 1.0f, 1.0f };

private:
    std::string m_Name;
    // Each Matter owns its Laws. Using Scope (unique_ptr) ensures automatic cleanup.
    std::vector<Scope<Law>> m_Laws;
};

// --- Template Method Implementations ---
// These must be in the header file.

template<typename T, typename... Args>
T* Matter::AddLaw(Args&&... args)
{
    // Ensure T is a type of Law
    static_assert(std::is_base_of<Law, T>::value, "T must be a derivative of Law");

    // Create a new Law of type T, passing any arguments to its constructor.
    Scope<T> newLaw = CreateScope<T>(std::forward<Args>(args)...);
    T* rawPtr = newLaw.get(); // Get the raw pointer before moving ownership.

    // Set the owner and call the creation hook.
    newLaw->SetOwner(this);
    newLaw->OnCreate();

    // Add the new law to our list.
    m_Laws.push_back(std::move(newLaw));

    return rawPtr;
}

template<typename T>
T* Matter::GetLaw()
{
    static_assert(std::is_base_of<Law, T>::value, "T must be a derivative of Law");

    for (const auto& law : m_Laws)
    {
        // Use dynamic_cast to safely check if the law is of the requested type.
        if (T* castedLaw = dynamic_cast<T*>(law.get()))
        {
            return castedLaw;
        }
    }
    return nullptr;
}

template<typename T>
void Matter::RemoveLaw()
{
    static_assert(std::is_base_of<Law, T>::value, "T must be a derivative of Law");

    auto it = std::remove_if(m_Laws.begin(), m_Laws.end(), [](const Scope<Law>& law) {
        return dynamic_cast<T*>(law.get()) != nullptr;
    });

    if (it != m_Laws.end())
    {
        // Call the destruction hook before erasing.
        (*it)->OnDestroy();
        m_Laws.erase(it);
    }
}

} // namespace Creative
