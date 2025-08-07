#pragma once

#include <chrono>

namespace Creative {

class Timer
{
public:
    Timer();

    // Call once per frame to update the delta time.
    void Tick();

    // Get the time in seconds between the last two frames.
    float GetDeltaTime() const;

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_LastTimePoint;
    float m_DeltaTime;
};

} // namespace Creative
