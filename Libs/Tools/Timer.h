#ifndef TIMER_H
#define TIMER_H
#include <cstdint>
#include <ctime>
#include <ratio>
#include <chrono>

namespace MGTools
{
    struct TimerData
    {
        double deltaTime;
        double now;
    };

    class FrameTimer
    {
    public:
        FrameTimer();
        TimerData GetFrameBasisTime();
    private:
        std::chrono::steady_clock::time_point m_lastUpdateTimePoint;
        std::chrono::steady_clock::time_point m_startTimePoint;
    };


}

#endif // TIMER_H
