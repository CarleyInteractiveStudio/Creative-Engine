#ifndef CREATIVE_ENGINE_TIME_H
#define CREATIVE_ENGINE_TIME_H

#include <chrono>

namespace Creative {

class Time {
public:
    static void Init();
    static void Update();
    static float GetDeltaTime(); // Returns time in seconds

private:
    Time() {} // Private constructor

    static std::chrono::time_point<std::chrono::high_resolution_clock> s_LastFrameTime;
    static float s_DeltaTime;
};

} // namespace Creative

#endif //CREATIVE_ENGINE_TIME_H
