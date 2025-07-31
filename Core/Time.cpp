#include "Time.h"

namespace Creative {

// Initialize static members
std::chrono::time_point<std::chrono::high_resolution_clock> Time::s_LastFrameTime;
float Time::s_DeltaTime = 0.0f;

void Time::Init() {
    s_LastFrameTime = std::chrono::high_resolution_clock::now();
}

void Time::Update() {
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = currentTime - s_LastFrameTime;
    s_DeltaTime = duration.count();
    s_LastFrameTime = currentTime;
}

float Time::GetDeltaTime() {
    return s_DeltaTime;
}

} // namespace Creative
