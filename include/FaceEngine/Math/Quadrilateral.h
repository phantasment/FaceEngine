#ifndef FACEENGINE_MATH_QUADRILATERAL
#define FACEENGINE_MATH_QUADRILATERAL

#include "FaceEngine/Math/Vector2.h"
#include "FaceEngine/Math/Rectangle.h"

namespace FaceEngine
{
    template <typename T>
    class Quadrilateral
    {
    static_assert(std::is_same<float, T>() || 
                      std::is_same<int, T>() || 
                      std::is_same<double, T>() || 
                      std::is_same<short, T>() ||
                      std::is_same<long, T>());

    public:
        Vector2f A, B, C, D;
        
        Quadrilateral<T>(const Vector2f& a, const Vector2f& b, const Vector2f& c, const Vector2f& d) noexcept;
        Quadrilateral<T>(const float a_X, const float a_Y, const float b_X, const float b_y, const float c_X, const float c_Y, const float d_X, const float d_Y) noexcept;
        Quadrilateral<T>(const Rectangle& rect) noexcept;
    };
}

#endif