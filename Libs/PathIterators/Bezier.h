#ifndef BEZIER_H
#define BEZIER_H
#include "../Tools/Vector2d.h"

namespace MGTools
{
template<typename ScalarType>
class Bezier2d
{
public:
    Bezier2d() {}
    Bezier2d(const Vector2d<ScalarType>& P0, const Vector2d<ScalarType>& P1)
    : m_pow(1), m_P0(P0), m_P1(P1) { }
    Bezier2d(const Vector2d<ScalarType>& P0, const Vector2d<ScalarType>& P1, const Vector2d<ScalarType>& P2)
    : m_pow(2), m_P0(P0), m_P1(P1), m_P2(P2) { }
    Bezier2d(const Vector2d<ScalarType>& P0, const Vector2d<ScalarType>& P1, const Vector2d<ScalarType>& P2, const Vector2d<ScalarType>& P3)
    : m_pow(3), m_P0(P0), m_P1(P1), m_P2(P2), m_P3(P3) { }

    Vector2d<ScalarType> Pos(double t) const
    {
        switch(m_pow)
        {
        case 1:
        {
            return Vector2d<ScalarType>(m_P0 + (m_P1 - m_P0) * t);
        }
        case 2:
        {
            auto tp = 1.0 - t;
            return Vector2d<ScalarType>((tp * tp) * m_P0 + (2 * t * tp) * m_P1 + (t * t) * m_P2);
        }
        case 3:
        {
            auto tp = 1.0 - t;
            auto tp2 = tp * tp;
            auto tp3 = tp2 * tp;
            auto t2 = t * t;
            auto t3 = t2 * t;

            return Vector2d<ScalarType>(tp3 * m_P0 + (3 * t * tp2) * m_P1 + (3 * t2 * tp) * m_P2 + t3 * m_P3);
        }
        default:
            break;
        }
        return Vector2d<ScalarType>();
    }

//private:
    int m_pow;
    Vector2d<double> m_P0;
    Vector2d<double> m_P1;
    Vector2d<double> m_P2;
    Vector2d<double> m_P3;
};
};
#endif // BEZIER_H
