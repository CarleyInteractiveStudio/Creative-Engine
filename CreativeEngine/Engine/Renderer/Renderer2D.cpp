#include "Renderer2D.h"

#include "Engine/SceneSpace/SceneSpace.h"
#include "Engine/MatterSystem/Laws/AppearanceLaw.h"
#include "Engine/Core/Log.h"

namespace Creative {

Renderer2D::Renderer2D()
{
    Log::Core_Info("2D Software Renderer created.");
}

void Renderer2D::Render(SceneSpace& scene, Image& targetImage)
{
    // First, clear the image to a background color.
    targetImage.Clear({ 15, 15, 20 }); // A nice dark blue

    // Get all the Matter objects from the scene.
    const auto& matters = scene.GetMatters();

    // Iterate through every Matter.
    for (const auto& matter : matters)
    {
        // Check if this Matter has an AppearanceLaw.
        AppearanceLaw* appearance = matter->GetLaw<AppearanceLaw>();
        if (appearance)
        {
            // If it does, draw it! We construct a Vec2 from the Matter's Vec3 position.
            DrawQuad(targetImage, {matter->position.x, matter->position.y}, appearance->size, appearance->color);
        }
    }
}

void Renderer2D::DrawQuad(Image& image, const Vec2& position, const Vec2& size, const Color& color)
{
    // This is a very simple quad drawing function.
    // It treats the position as the center of the quad.
    // It doesn't handle rotation or camera transformations yet.

    // Calculate the top-left and bottom-right corners of the rectangle.
    // We cast to int because we are drawing to discrete pixels.
    int halfWidth = static_cast<int>(size.x / 2.0f);
    int halfHeight = static_cast<int>(size.y / 2.0f);

    // We need to account for the image's coordinate system (0,0 is top-left)
    // and our world's coordinate system (0,0 could be center of the screen).
    // For now, let's assume a simple mapping where the world center is the image center.
    int screenCenterX = image.GetWidth() / 2;
    int screenCenterY = image.GetHeight() / 2;

    int centerX = screenCenterX + static_cast<int>(position.x);
    int centerY = screenCenterY - static_cast<int>(position.y); // Y is inverted in screen coordinates

    int startX = centerX - halfWidth;
    int endX = centerX + halfWidth;
    int startY = centerY - halfHeight;
    int endY = centerY + halfHeight;

    // Loop through every pixel of the quad's bounding box and set its color.
    for (int y = startY; y < endY; ++y)
    {
        for (int x = startX; x < endX; ++x)
        {
            // We must still check bounds in case the quad is partially off-screen.
            // The SetPixel method already does this, so we don't need to repeat it here.
            image.SetPixel(x, y, color);
        }
    }
}

} // namespace Creative
