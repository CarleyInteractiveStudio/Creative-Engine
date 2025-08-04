#pragma once

// Forward-declarations to avoid including full headers here.
namespace Creative {
    class SceneSpace;
    class Image;
    struct Vec2;
    struct Color;
}

namespace Creative {

// Renderer2D is responsible for drawing a 2D representation of a SceneSpace
// onto a target Image.
class Renderer2D
{
public:
    Renderer2D();

    // Renders a single frame of the scene.
    void Render(SceneSpace& scene, Image& targetImage);

private:
    // A helper function to draw a simple, solid-colored rectangle.
    void DrawQuad(Image& image, const Vec2& position, const Vec2& size, const Color& color);
};

} // namespace Creative
