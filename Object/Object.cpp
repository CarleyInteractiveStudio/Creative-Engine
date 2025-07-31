#include "Object.h"

namespace Creative {

Object::Object(const std::string& name) : m_Name(name) {}

void Object::Init() {
    // Note: Components are initialized upon being added in AddComponent.
    // This Init could be used for object-level initialization if needed in the future.
}

void Object::Update(float deltaTime) {
    for (auto& component : m_Components) {
        component->Update(deltaTime);
    }
}

void Object::Shutdown() {
    // Shutdown components in reverse order of addition
    for (auto it = m_Components.rbegin(); it != m_Components.rend(); ++it) {
        (*it)->Shutdown();
    }
    m_Components.clear();
}

} // namespace Creative
