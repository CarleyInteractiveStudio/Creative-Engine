#ifndef CREATIVE_ENGINE_OBJECT_H
#define CREATIVE_ENGINE_OBJECT_H

#include "Component.h"
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <type_traits> // For std::is_base_of

namespace Creative {

class Object {
public:
    Object(const std::string& name = "Object");
    ~Object() = default;

    void Init();
    void Update(float deltaTime);
    void Shutdown();

    // Adds a component of type T to the object.
    // TArgs are the arguments for the component's constructor.
    template<typename T, typename... TArgs>
    T* AddComponent(TArgs&&... args) {
        static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

        auto newComponent = std::make_unique<T>(std::forward<TArgs>(args)...);
        T* componentPtr = newComponent.get();
        componentPtr->SetOwner(this);

        m_Components.push_back(std::move(newComponent));

        componentPtr->Init(); // Initialize the component after it's been added

        return componentPtr;
    }

    // Gets a component of type T from the object.
    template<typename T>
    T* GetComponent() {
        static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

        for (const auto& component : m_Components) {
            if (T* casted = dynamic_cast<T*>(component.get())) {
                return casted;
            }
        }
        return nullptr;
    }

    const std::string& GetName() const { return m_Name; }
    void SetName(const std::string& name) { m_Name = name; }

private:
    std::string m_Name;
    std::vector<std::unique_ptr<Component>> m_Components;
};

} // namespace Creative

#endif //CREATIVE_ENGINE_OBJECT_H
