#include "FaceEngine/Math/Circle.h"

namespace FaceEngine
{
    Circle::Circle(const Vector2f& position, const float radius) noexcept
    {
        Position = position;
        Radius = radius;
    }

    Circle::Circle(const float x, const float y, const float radius) noexcept
    {
        Position = Vector2f(x, y);
        Radius = radius;
    }

    std::string Circle::ToString() const noexcept
    {
        return "Circle[X: " + std::to_string(Position.X) + ", Y: " + std::to_string(Position.Y) + ", Radius: " + std::to_string(Radius) + "]";
    }

    bool Circle::Equals(const Circle& circle) const noexcept
    {
        return Position == circle.Position && Radius == circle.Radius;
    }

    bool Circle::Contains(const Vector2f& vector) const noexcept
    {
        return Position.Distance(vector) <= Radius;
    }

    bool Circle::CompletelyContains(const Vector2f& vector) const noexcept
    {
        return Position.Distance(vector) < Radius;
    }
}

bool operator==(const FaceEngine::Circle& firstCircle, const FaceEngine::Circle& secondCircle) noexcept
{
    return firstCircle.Equals(secondCircle);
}

bool operator!=(const FaceEngine::Circle& firstCircle, const FaceEngine::Circle& secondCircle) noexcept
{
    return !firstCircle.Equals(secondCircle);
}
