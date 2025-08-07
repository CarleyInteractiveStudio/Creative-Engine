#pragma once

namespace Creative {

class Matter; // Forward-declaration to avoid circular include with Matter.h

// Law is the abstract base class for all components that define behavior.
// It's an "interface" that defines a contract for how a Law interacts with the engine.
// Each specific Law (e.g., MotionLaw, RenderLaw, PhysicsLaw) will inherit from this.
class Law
{
public:
    Law() = default;
    virtual ~Law() = default;

    // --- Lifecycle Hooks ---
    // These methods are called by the engine at specific times.

    // Called once when the Law is first attached to a Matter object.
    virtual void OnCreate() {}

    // Called every frame of the game loop.
    // `deltaTime` is the time in seconds since the last frame.
    virtual void OnUpdate(float deltaTime) {}

    // Called when the Law is removed or its owner Matter is destroyed.
    virtual void OnDestroy() {}

    // Called by the Matter class to give this Law a reference to its owner.
    void SetOwner(Matter* owner) { m_Owner = owner; }

protected:
    // A pointer back to the Matter object that owns this Law.
    // This allows a Law to access other Laws on the same object, or its transform.
    Matter* m_Owner = nullptr;
};

} // namespace Creative
