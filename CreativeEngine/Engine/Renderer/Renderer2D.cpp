#include "Renderer2D.h"
#include "Camera2D.h" // Include the new camera header

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
    // 1. Find the active camera in the scene.
    Camera2D* activeCamera = nullptr;
    for (const auto& matter : scene.GetMatters())
    {
        // Try to cast the Matter pointer to a Camera2D pointer.
        if (auto cam = dynamic_cast<Camera2D*>(matter.get()))
        {
            if (cam->isPrimary)
            {
                activeCamera = cam;
                break; // Found it, stop searching.
            }
        }
    }

    // If there's no camera, we can't render anything.
    if (!activeCamera)
    {
        Log::Core_Warn("Renderer2D: No primary camera found in the scene. Cannot render.");
        targetImage.Clear({255, 0, 255}); // Draw magenta to indicate an error.
        return;
    }

    // 2. Calculate transformation values from the camera.
    // This determines how many pixels one "world unit" is.
    const float pixelsPerUnit = static_cast<float>(targetImage.GetHeight()) / activeCamera->orthographicSize;
    const Vec2 cameraPos = { activeCamera->position.x, activeCamera->position.y };

    // 3. Clear the image and render all visible objects.
    targetImage.Clear({ 15, 15, 20 }); // A nice dark blue

    for (const auto& matter : scene.GetMatters())
    {
        // Don't try to draw the camera itself.
        if (matter.get() == activeCamera)
        {
            continue;
        }

        if (auto appearance = matter->GetLaw<AppearanceLaw>())
        {
            // 4. Transform object's world position to camera-relative coordinates.
            const Vec2 objectPos = { matter->position.x, matter->position.y };
            const Vec2 relativePos = { objectPos.x - cameraPos.x, objectPos.y - cameraPos.y };

            // 5. Scale the position and size by the camera's zoom level (pixelsPerUnit).
            const Vec2 screenPos = { relativePos.x * pixelsPerUnit, relativePos.y * pixelsPerUnit };
            const Vec2 screenSize = { appearance->size.x * pixelsPerUnit, appearance->size.y * pixelsPerUnit };

            // 6. Draw the final, transformed quad.
            DrawQuad(targetImage, screenPos, screenSize, appearance->color);
        }
    }
}

void Renderer2D::DrawQuad(Image& image, const Vec2& screenPos, const Vec2& screenSize, const Color& color)
{
    // The incoming `screenPos` is now in pixels, relative to the center of the screen.
    // The `screenSize` is also in pixels.

    const int halfWidth = static_cast<int>(screenSize.x / 2.0f);
    const int halfHeight = static_cast<int>(screenSize.y / 2.0f);

    // Find the center of the image.
    const int screenCenterX = image.GetWidth() / 2;
    const int screenCenterY = image.GetHeight() / 2;

    // Calculate the final pixel coordinates for the quad's center.
    // Y is inverted because in our world +Y is up, but in image coordinates +Y is down.
    const int centerX = screenCenterX + static_cast<int>(screenPos.x);
    const int centerY = screenCenterY - static_cast<int>(screenPos.y);

    const int startX = centerX - halfWidth;
    const int endX = centerX + halfWidth;
    const int startY = centerY - halfHeight;
    const int endY = centerY + halfHeight;

    // Loop through every pixel of the quad's bounding box and set its color.
    for (int y = startY; y < endY; ++y)
    {
        for (int x = startX; x < endX; ++x)
        {
            image.SetPixel(x, y, color);
        }
    }
}

} // namespace Creative
