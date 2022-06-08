#include "FaceEngine/Math/Calculator.h"

#include <cmath>

namespace FaceEngine
{
    float Calculator::DegreesToRadians(float angle)
    {
        return angle * Pi / 180.0f;
    }

    float Calculator::RadiansToDegrees(float angle)
    {
        return angle * 180.0f / Pi;
    }

    float Calculator::WrapAngle(float angle)
    {
        return angle - ((float) floorf(angle / 360.0f) * 360.0f);
    }

    float Calculator::WrapAngle180(float angle)
    {
        float wrappedAngle = WrapAngle(angle);

        if (wrappedAngle > 180.0f)
        {
            wrappedAngle = -(360.0f - wrappedAngle);
        }

        return wrappedAngle;
    }

    float Calculator::Lerp(const float a, const float b, const float t)
    {
        return (1.0f - t) * a + t * b;
    }
}