#include "Engine/Platform/Timer.h"

namespace Creative {

Timer::Timer()
    // Initialize the last time point to the current time when the timer is created.
    : m_LastTimePoint(std::chrono::high_resolution_clock::now())
    , m_DeltaTime(0.0f) // Initial delta time is zero.
{
}

void Timer::Tick()
{
    // Get the current time.
    auto currentTimePoint = std::chrono::high_resolution_clock::now();

    // Calculate the duration between the current frame and the last frame.
    // The result is a float representing the duration in seconds.
    std::chrono::duration<float, std::chrono::seconds::period> duration = currentTimePoint - m_LastTimePoint;

    // Store the delta time.
    m_DeltaTime = duration.count();

    // Update the last time point for the next frame's calculation.
    m_LastTimePoint = currentTimePoint;
}

// Returns the time between the last two calls to Tick(), in seconds.
float Timer::GetDeltaTime() const
{
    return m_DeltaTime;
}

} // namespace Creative
