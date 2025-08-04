#include "Renderer2D.h"
#include "Camera2D.h"
#include "Engine/SceneSpace/SceneSpace.h"
#include "Engine/MatterSystem/Laws/AppearanceLaw.h"
#include "Engine/MatterSystem/Laws/SpriteLaw.h"
#include "Engine/Core/Log.h"

#include <cmath>
#include <algorithm>
#include <vector>

namespace Creative {

Renderer2D::Renderer2D()
{
    Log::Core_Info("2D Software Renderer created.");
}

void Renderer2D::Render(SceneSpace& scene, Image& targetImage)
{
    // 1. Find the active camera
    Camera2D* activeCamera = nullptr;
    for (const auto& matter : scene.GetMatters())
    {
        if (auto cam = dynamic_cast<Camera2D*>(matter.get()))
        {
            if (cam->isPrimary) { activeCamera = cam; break; }
        }
    }

    if (!activeCamera)
    {
        Log::Core_Warn("Renderer2D: No primary camera found. Cannot render.");
        targetImage.Clear({255, 0, 255});
        return;
    }

    // 2. Calculate camera transforms
    const float pixelsPerUnit = static_cast<float>(targetImage.GetHeight()) / activeCamera->orthographicSize;
    const Vec2 cameraPos = { activeCamera->position.x, activeCamera->position.y };
    const int screenCenterX = targetImage.GetWidth() / 2;
    const int screenCenterY = targetImage.GetHeight() / 2;

    targetImage.Clear({ 15, 15, 20 });

    for (const auto& matter : scene.GetMatters())
    {
        if (matter.get() == activeCamera) continue;

        auto* appearance = matter->GetLaw<AppearanceLaw>();
        if (!appearance) continue;

        // 3. Transform object properties to screen space
        const Vec2 objectPos = { matter->position.x, matter->position.y };
        const Vec2 relativePos = { objectPos.x - cameraPos.x, objectPos.y - cameraPos.y };
        const Vec2 screenPos = { relativePos.x * pixelsPerUnit, relativePos.y * pixelsPerUnit };
        const Vec2 screenSize = { appearance->size.x * pixelsPerUnit, appearance->size.y * pixelsPerUnit };
        const Vec2 finalCenterPos = { (float)screenCenterX + screenPos.x, (float)screenCenterY - screenPos.y };

        // 4. Decide how to fill the shape (texture or solid color)
        auto* sprite = matter->GetLaw<SpriteLaw>();
        if (sprite && sprite->spriteImage.GetWidth() > 0)
        {
            // If a valid SpriteLaw exists, use its texture and UV properties.
            DrawRotatedQuad(targetImage, finalCenterPos, screenSize, matter->rotation.z, sprite->spriteImage, sprite->uvOffset, sprite->uvScale);
        }
        else
        {
            // Otherwise, use the solid color from the AppearanceLaw.
            DrawRotatedQuad(targetImage, finalCenterPos, screenSize, matter->rotation.z, appearance->color);
        }
    }
}

// --- Solid Color Implementation ---

void Renderer2D::DrawRotatedQuad(Image& targetImage, const Vec2& centerPos, const Vec2& size, float angleRad, const Color& color)
{
    Vec2 p[4];
    float w = size.x;
    float h = size.y;
    float s = sinf(angleRad);
    float c = cosf(angleRad);

    p[0] = { centerPos.x + (-w/2*c - -h/2*s), centerPos.y + (-w/2*s + -h/2*c) };
    p[1] = { centerPos.x + ( w/2*c - -h/2*s), centerPos.y + ( w/2*s + -h/2*c) };
    p[2] = { centerPos.x + ( w/2*c -  h/2*s), centerPos.y + ( w/2*s +  h/2*c) };
    p[3] = { centerPos.x + (-w/2*c -  h/2*s), centerPos.y + (-w/2*s +  h/2*c) };

    FillTriangle(targetImage, p[0], p[1], p[2], color);
    FillTriangle(targetImage, p[0], p[2], p[3], color);
}

void Renderer2D::FillTriangle(Image& targetImage, Vec2 p0, Vec2 p1, Vec2 p2, const Color& color)
{
    auto edge_function = [](const Vec2& a, const Vec2& b, const Vec2& p) {
        return (p.x - a.x) * (b.y - a.y) - (p.y - a.y) * (b.x - a.x);
    };

    const int minX = std::max(0, (int)std::floor(std::min({p0.x, p1.x, p2.x})));
    const int maxX = std::min((int)targetImage.GetWidth(), (int)std::ceil(std::max({p0.x, p1.x, p2.x})));
    const int minY = std::max(0, (int)std::floor(std::min({p0.y, p1.y, p2.y})));
    const int maxY = std::min((int)targetImage.GetHeight(), (int)std::ceil(std::max({p0.y, p1.y, p2.y})));

    for (int y = minY; y < maxY; ++y) {
        for (int x = minX; x < maxX; ++x) {
            Vec2 p = { (float)x + 0.5f, (float)y + 0.5f };
            float w0 = edge_function(p1, p2, p);
            float w1 = edge_function(p2, p0, p);
            float w2 = edge_function(p0, p1, p);
            if ((w0 >= 0 && w1 >= 0 && w2 >= 0) || (w0 <= 0 && w1 <= 0 && w2 <= 0)) {
                 targetImage.SetPixel(x, y, color);
            }
        }
    }
}

// --- Textured Implementation ---

void Renderer2D::DrawRotatedQuad(Image& targetImage, const Vec2& centerPos, const Vec2& size, float angleRad, const Image& texture, const Vec2& uvOffset, const Vec2& uvScale)
{
    Vec2 p[4];
    float w = size.x;
    float h = size.y;
    float s = sinf(angleRad);
    float c = cosf(angleRad);

    p[0] = { centerPos.x + (-w/2*c - -h/2*s), centerPos.y + (-w/2*s + -h/2*c) };
    p[1] = { centerPos.x + ( w/2*c - -h/2*s), centerPos.y + ( w/2*s + -h/2*c) };
    p[2] = { centerPos.x + ( w/2*c -  h/2*s), centerPos.y + ( w/2*s +  h/2*c) };
    p[3] = { centerPos.x + (-w/2*c -  h/2*s), centerPos.y + (-w/2*s +  h/2*c) };

    // Calculate UVs based on the offset and scale from the SpriteLaw
    Vec2 uv[4] = {
        { uvOffset.x, uvOffset.y + uvScale.y },                 // Bottom-left
        { uvOffset.x + uvScale.x, uvOffset.y + uvScale.y },     // Bottom-right
        { uvOffset.x + uvScale.x, uvOffset.y },                 // Top-right
        { uvOffset.x, uvOffset.y }                              // Top-left
    };

    FillTriangle(targetImage, p[0], p[1], p[2], uv[0], uv[1], uv[2], texture);
    FillTriangle(targetImage, p[0], p[2], p[3], uv[0], uv[2], uv[3], texture);
}

void Renderer2D::FillTriangle(Image& targetImage, Vec2 p0, Vec2 p1, Vec2 p2, Vec2 uv0, Vec2 uv1, Vec2 uv2, const Image& texture)
{
    auto edge_function = [](const Vec2& a, const Vec2& b, const Vec2& p) {
        return (p.x - a.x) * (b.y - a.y) - (p.y - a.y) * (b.x - a.x);
    };

    const int minX = std::max(0, (int)std::floor(std::min({p0.x, p1.x, p2.x})));
    const int maxX = std::min((int)targetImage.GetWidth(), (int)std::ceil(std::max({p0.x, p1.x, p2.x})));
    const int minY = std::max(0, (int)std::floor(std::min({p0.y, p1.y, p2.y})));
    const int maxY = std::min((int)targetImage.GetHeight(), (int)std::ceil(std::max({p0.y, p1.y, p2.y})));

    const float area = edge_function(p0, p1, p2);
    if (std::abs(area) < 1e-5) return;

    for (int y = minY; y < maxY; ++y) {
        for (int x = minX; x < maxX; ++x) {
            Vec2 p = { (float)x + 0.5f, (float)y + 0.5f };
            float w0 = edge_function(p1, p2, p);
            float w1 = edge_function(p2, p0, p);
            float w2 = edge_function(p0, p1, p);

            if ((w0 >= 0 && w1 >= 0 && w2 >= 0) || (w0 <= 0 && w1 <= 0 && w2 <= 0))
            {
                float alpha = w0 / area;
                float beta = w1 / area;
                float gamma = w2 / area;

                float u = alpha * uv0.x + beta * uv1.x + gamma * uv2.x;
                float v = alpha * uv0.y + beta * uv1.y + gamma * uv2.y;

                int texX = static_cast<int>(u * texture.GetWidth());
                int texY = static_cast<int>(v * texture.GetHeight());

                texX = std::max(0, std::min(texX, (int)texture.GetWidth() - 1));
                texY = std::max(0, std::min(texY, (int)texture.GetHeight() - 1));

                const Color& texColor = texture.GetData()[texY * texture.GetWidth() + texX];

                targetImage.SetPixel(x, y, texColor);
            }
        }
    }
}

} // namespace Creative
