#ifndef VECTOR2D_H
#define VECTOR2D_H

namespace MGTools
{

template<typename T>
class Vector2d
{
public:
    Vector2d() = default;
    Vector2d(T x, T y) : m_x(x), m_y(y) {}
    template<typename ScalarT>
    Vector2d(const Vector2d<ScalarT>& v)
        : m_x(static_cast<double>(v.X())), m_y(static_cast<double>(v.Y())) { }

    T X() const { return m_x; }
    T Y() const { return m_y; }
    void SetX(T x) { m_x = x; }
    void SetY(T y) { m_y = y; }

    // Scalar
    template<typename ScalarT>
    Vector2d<T>& operator *=(const ScalarT& val)
    {
        m_x *= val;
        m_y *= val;
        return *this;
    }
    template<typename ScalarT>
    Vector2d<T>& operator /=(const ScalarT& val)
    {
        m_x /= val;
        m_y /= val;
        return *this;
    }
    template<typename ScalarT>
    Vector2d<T>& operator +=(const ScalarT& val)
    {
        m_x += val;
        m_y += val;
        return *this;
    }
    template<typename ScalarT>
    Vector2d<T>& operator -=(const ScalarT& val)
    {
        m_x -= val;
        m_y -= val;
        return *this;
    }

    // Vector
    template<typename ScalarT>
    Vector2d<T>& operator *=(const Vector2d<ScalarT>& val)
    {
        m_x *= val.m_x;
        m_y *= val.m_y;
        return *this;
    }
    template<typename ScalarT>
    Vector2d<T>& operator /=(const Vector2d<ScalarT>& val)
    {
        m_x /= val.m_x;
        m_y /= val.m_y;
        return *this;
    }
    template<typename ScalarT>
    Vector2d<T>& operator +=(const Vector2d<ScalarT>& val)
    {
        m_x += val.m_x;
        m_y += val.m_y;
        return *this;
    }
    template<typename ScalarT>
    Vector2d<T>& operator -=(const Vector2d<ScalarT>& val)
    {
        m_x -= val.m_x;
        m_y -= val.m_y;
        return *this;
    }


private:
    T   m_x;
    T   m_y;
};

// Scalar
template<typename LeftType, typename RightType>
Vector2d<LeftType> operator*( Vector2d<LeftType> lhs, const RightType& rhs )
{
    lhs *= rhs;
    return lhs;
}
template<typename LeftType, typename RightType>
Vector2d<LeftType> operator/( Vector2d<LeftType> lhs, const RightType& rhs )
{
    lhs /= rhs;
    return lhs;
}
template<typename LeftType, typename RightType>
Vector2d<LeftType> operator+( Vector2d<LeftType> lhs, const RightType& rhs )
{
    lhs += rhs;
    return lhs;
}
template<typename LeftType, typename RightType>
Vector2d<LeftType> operator-( Vector2d<LeftType> lhs, const RightType& rhs )
{
    lhs -= rhs;
    return lhs;
}
//
template<typename LeftType, typename RightType>
Vector2d<RightType> operator*( const LeftType& lhs, Vector2d<RightType> rhs )
{
    rhs *= lhs;
    return rhs;
}
template<typename LeftType, typename RightType>
Vector2d<RightType> operator/( const LeftType& lhs, Vector2d<RightType> rhs )
{
    rhs /= lhs;
    return rhs;
}
template<typename LeftType, typename RightType>
Vector2d<RightType> operator+( const LeftType& lhs, Vector2d<RightType> rhs )
{
    rhs += lhs;
    return rhs;
}
template<typename LeftType, typename RightType>
Vector2d<RightType> operator-( const LeftType& lhs, Vector2d<RightType> rhs )
{
    rhs -= lhs;
    return rhs;
}
// Vector
template<typename LeftType, typename RightType>
Vector2d<LeftType> operator*( Vector2d<LeftType> lhs, const Vector2d<RightType>& rhs )
{
    lhs *= rhs;
    return lhs;
}
template<typename LeftType, typename RightType>
Vector2d<LeftType> operator/( Vector2d<LeftType> lhs, const Vector2d<RightType>& rhs )
{
    lhs /= rhs;
    return lhs;
}
template<typename LeftType, typename RightType>
Vector2d<LeftType> operator+( Vector2d<LeftType> lhs, const Vector2d<RightType>& rhs )
{
    lhs += rhs;
    return lhs;
}
template<typename LeftType, typename RightType>
Vector2d<LeftType> operator-( Vector2d<LeftType> lhs, const Vector2d<RightType>& rhs )
{
    lhs -= rhs;
    return lhs;
}

};
#endif // VECTOR2D_H
