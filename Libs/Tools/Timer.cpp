#include "Timer.h"


using namespace std::chrono;
using namespace MGTools;

///////////////////////////////////////////////////////////////////////////
FrameTimer::FrameTimer()
{
    m_startTimePoint = steady_clock::now();
    m_lastUpdateTimePoint = m_startTimePoint;
}

///////////////////////////////////////////////////////////////////////////
TimerData FrameTimer::GetFrameBasisTime()
{
    steady_clock::time_point now = steady_clock::now();
    duration<double> timeSpan = duration_cast<duration<double>>(now - m_lastUpdateTimePoint);
    duration<double> nowTimeSpan = duration_cast<duration<double>>(now - m_startTimePoint);
    m_lastUpdateTimePoint = now;

    TimerData tData;
    tData.deltaTime = timeSpan.count();
    tData.now = nowTimeSpan.count();

    return tData;
}
