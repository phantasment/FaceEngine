#ifndef FACEENGINE_MATH_CIRCLE_H_
#define FACEENGINE_MATH_CIRCLE_H_

#include "FaceEngine/Math/Vector2f.h"

namespace FaceEngine
{
    class Circle
    {
    public:
        Vector2f Position;
        float Radius;

        Circle(const Vector2f& position, const float radius) noexcept;
        Circle(const float x, const float y, const float radius) noexcept;
        ~Circle();

        std::string ToString() const noexcept;

        bool Equals(const Circle& circle) const noexcept;

        bool Contains(const Vector2f& vector) const noexcept;
        bool CompletelyContains(const Vector2f& vector) const noexcept;
    };
}

bool operator==(const FaceEngine::Circle& firstCircle, const FaceEngine::Circle& secondCircle) noexcept;
bool operator!=(const FaceEngine::Circle& firstCircle, const FaceEngine::Circle& secondCircle) noexcept;

#endif