#pragma once

#include "Engine/MatterSystem/Law.h"
#include "Engine/Renderer/Image.h" // For the Color struct
#include "Engine/Core/Math.h"     // For Vec2 size

namespace Creative {

// AppearanceLaw is a concrete Law that holds data about how a Matter should be rendered.
// In this simple 2D case, it just stores a size and a color.
class AppearanceLaw : public Law
{
public:
    AppearanceLaw(const Vec2& size, const Color& color)
        : size(size), color(color)
    {}

    // This particular Law is a pure data container, so it doesn't need to
    // implement any of the lifecycle methods like OnUpdate or OnCreate.

    Vec2 size;
    Color color;
};

} // namespace Creative
