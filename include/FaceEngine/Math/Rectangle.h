#ifndef FACEENGINE_MATH_RECTANGLE_H_
#define FACEENGINE_MATH_RECTANGLE_H_

#include "FaceEngine/Math/Vector2f.h"
#include <iostream>

namespace FaceEngine
{
    class Rectangle
    {
    public:
        float X;
        float Y;
        float Width;
        float Height;

        Rectangle();
        Rectangle(const Vector2f& position, const float& width, const float& height);
        Rectangle(const float& x, const float& y, const float& width, const float& height);

        float GetTop() const;
        float GetBottom() const;
        float GetLeft() const;
        float GetRight() const;

        Vector2f GetPosition() const;
        Vector2f GetSize() const;

        bool Contains(const Vector2f& vector) const;
        bool CompletelyContains(const Vector2f& vector) const;
        bool Contains(const Rectangle& rect) const;
        bool CompletelyContains(const Rectangle& rect) const;
        bool Intersects(const Rectangle& rect) const;
        bool IntersectsOrTouches(const Rectangle& rect) const;
        bool Equals(const Rectangle& rect) const;

        void operator +=(const Rectangle& rect) noexcept;
    };
}

std::ostream& operator <<(std::ostream& out, const FaceEngine::Rectangle& rect);
FaceEngine::Rectangle operator+(const FaceEngine::Rectangle& firstRect, const FaceEngine::Rectangle& secondRect) noexcept;
bool operator==(const FaceEngine::Rectangle& firstRect, const FaceEngine::Rectangle& secondRect) noexcept;
bool operator!=(const FaceEngine::Rectangle& firstRect, const FaceEngine::Rectangle& secondRect) noexcept;

#endif