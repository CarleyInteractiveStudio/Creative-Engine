#pragma once

#include "Engine/MatterSystem/Law.h"
#include "Engine/Renderer/Image.h"
#include "Engine/Core/Math.h"
#include <string>

namespace Creative {

// SpriteLaw holds the visual representation of a Matter as a sprite (an image).
class SpriteLaw : public Law
{
public:
    // Constructor loads the sprite image from a given file path.
    SpriteLaw(const std::string& spritePath);
    virtual ~SpriteLaw() = default;

    // The actual image data for the sprite.
    // This is public for easy access by the Renderer. A more complex engine might
    // use an asset management system and store a handle/ID here instead.
    Image spriteImage;

    // --- For Sprite-sheet animations ---
    // Defines the sub-rectangle of the texture to use.
    // Coordinates are in UV space (0.0 to 1.0).
    Vec2 uvOffset = { 0.0f, 0.0f }; // Top-left corner of the sub-rectangle
    Vec2 uvScale  = { 1.0f, 1.0f }; // Size of the sub-rectangle
};

} // namespace Creative
