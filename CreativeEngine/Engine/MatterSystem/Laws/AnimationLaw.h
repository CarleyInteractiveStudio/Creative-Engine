#pragma once

#include "Engine/MatterSystem/Law.h"

namespace Creative {

// The AnimationLaw component is responsible for driving sprite-sheet animations.
// It works in conjunction with a SpriteLaw on the same Matter object.
// In its OnUpdate, it calculates the current animation frame and updates the
// uvOffset and uvScale on the SpriteLaw.
class AnimationLaw : public Law
{
public:
    AnimationLaw(int frameCount, float framesPerSecond, int columns, int rows);
    virtual ~AnimationLaw() = default;

    void OnUpdate(float deltaTime) override;

public:
    // --- Animation Properties ---
    int   m_FrameCount;
    float m_FramesPerSecond;
    int   m_Columns; // Number of columns in the sprite sheet
    int   m_Rows;    // Number of rows in the sprite sheet

private:
    float m_Timer = 0.0f;
    int   m_CurrentFrame = 0;
};

} // namespace Creative
