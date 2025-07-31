#ifndef CREATIVE_ENGINE_COMPONENT_H
#define CREATIVE_ENGINE_COMPONENT_H

namespace Creative {

class Object; // Forward declaration to avoid circular dependency

class Component {
public:
    Component() : m_Owner(nullptr) {}
    virtual ~Component() = default;

    // Called when the component is added to an Object
    virtual void Init() {}
    // Called every frame
    virtual void Update(float deltaTime) {}
    // Called when the component is removed or the Object is destroyed
    virtual void Shutdown() {}

    void SetOwner(Object* owner) { m_Owner = owner; }
    Object* GetOwner() const { return m_Owner; }

protected:
    Object* m_Owner;
};

} // namespace Creative

#endif //CREATIVE_ENGINE_COMPONENT_H
