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
    // --- Solid Color Rendering ---
    // Draws a solid-colored, rotated rectangle.
    void DrawRotatedQuad(Image& targetImage, const Vec2& centerPos, const Vec2& size, float angleRad, const Color& color);
    // Fills a solid-colored triangle.
    void FillTriangle(Image& targetImage, Vec2 p0, Vec2 p1, Vec2 p2, const Color& color);

    // --- Textured Rendering ---
    // Draws a textured, rotated rectangle, allowing for a sub-rectangle of the texture to be used.
    void DrawRotatedQuad(Image& targetImage, const Vec2& centerPos, const Vec2& size, float angleRad, const Image& texture, const Vec2& uvOffset, const Vec2& uvScale);
    // Fills a textured triangle using barycentric interpolation for UVs.
    void FillTriangle(Image& targetImage, Vec2 p0, Vec2 p1, Vec2 p2, Vec2 uv0, Vec2 uv1, Vec2 uv2, const Image& texture);
};

} // namespace Creative
