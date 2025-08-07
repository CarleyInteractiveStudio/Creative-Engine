#include "AnimationLaw.h"
#include "SpriteLaw.h"
#include "Engine/MatterSystem/Matter.h" // For m_Owner
#include "Engine/Core/Log.h"

namespace Creative {

AnimationLaw::AnimationLaw(int frameCount, float framesPerSecond, int columns, int rows)
    : m_FrameCount(frameCount)
    , m_FramesPerSecond(framesPerSecond)
    , m_Columns(columns)
    , m_Rows(rows)
{
}

void AnimationLaw::OnUpdate(float deltaTime)
{
    // If there's no animation to play, do nothing.
    if (m_FramesPerSecond <= 0.0f || m_FrameCount <= 1)
    {
        return;
    }

    // Get the SpriteLaw from the same Matter object.
    // We need this to update its UVs.
    SpriteLaw* spriteLaw = m_Owner->GetLaw<SpriteLaw>();
    if (!spriteLaw)
    {
        // This animation law can't do anything without a SpriteLaw to animate.
        return;
    }

    // Update the timer and calculate the current frame.
    m_Timer += deltaTime;
    m_CurrentFrame = static_cast<int>(m_Timer * m_FramesPerSecond) % m_FrameCount;

    // Calculate the UV scale (size of one frame in UV space)
    spriteLaw->uvScale.x = 1.0f / static_cast<float>(m_Columns);
    spriteLaw->uvScale.y = 1.0f / static_cast<float>(m_Rows);

    // Calculate the column and row of the current frame
    const int col = m_CurrentFrame % m_Columns;
    const int row = m_CurrentFrame / m_Columns;

    // Calculate the UV offset (top-left corner of the current frame in UV space)
    spriteLaw->uvOffset.x = static_cast<float>(col) * spriteLaw->uvScale.x;
    spriteLaw->uvOffset.y = static_cast<float>(row) * spriteLaw->uvScale.y;
}

} // namespace Creative
