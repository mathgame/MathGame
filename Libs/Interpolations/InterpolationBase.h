#ifndef INTERPOLATIONBASE_H
#define INTERPOLATIONBASE_H
#include "../Tools/Timer.h"

namespace MGTools {

template<typename VariableType>
class InterpolationBase
{
public:
    InterpolationBase(){}
    virtual void Update( TimerData tData ) = 0;
    virtual VariableType GetValue() const = 0;
protected:

};

template<typename VariableType>
class LinearInterpolation : public InterpolationBase<VariableType>
{
public:
    LinearInterpolation(){};
    LinearInterpolation(VariableType startValue, double speedPerSecond, TimerData startTime);
    virtual void Update( TimerData tData );
    virtual VariableType GetValue() const { return m_value; }
    void SetValue(VariableType value) { m_value = value; }

private:
    VariableType m_value;
    TimerData m_startTime;
    TimerData m_lastChangeTime;
    double m_speed;
};

template<typename VariableType>
LinearInterpolation<VariableType>::LinearInterpolation(VariableType startValue, double speedPerSecond, TimerData startTime)
    : m_value(startValue)
    , m_startTime(startTime)
    , m_lastChangeTime(startTime)
    , m_speed(speedPerSecond)
{
}

template<typename VariableType>
void LinearInterpolation<VariableType>::Update( TimerData tData )
{
    double duration = tData.now - m_lastChangeTime.now;
    double delta = m_speed * duration;
    VariableType newValue = m_value + delta;

    if (newValue != m_value)
    {
        m_value = newValue;
        m_lastChangeTime.now = tData.now;
    }
}

};

#endif // INTERPOLATIONBASE_H
