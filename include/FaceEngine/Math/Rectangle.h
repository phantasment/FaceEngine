#ifndef FACEENGINE_MATH_RECTANGLE_H_
#define FACEENGINE_MATH_RECTANGLE_H_

#include "FaceEngine/Math/Vector2.h"
#include <iostream>
#include <cstdint>

namespace FaceEngine
{
    template <typename T>
    class Rectangle
    {
        static_assert(std::is_same<float, T>() || 
                      std::is_same<std::int32_t, T>() || 
                      std::is_same<double, T>() || 
                      std::is_same<std::int16_t, T>() ||
                      std::is_same<std::int64_t, T>());

    public:
        T X;
        T Y;
        T Width;
        T Height;

        inline Rectangle()
        {
            X = 0;
            Y = 0;
            Width = 0;
            Height = 0;
        }

        inline Rectangle(const Vector2f& position, const T width, const T height)
        {
            X = position.X;
            Y = position.Y;
            Width = width;
            Height = height;
        }

        inline Rectangle(const T x, const T y, const T width, const T height)
        {
            X = x;
            Y = y;
            Width = width;
            Height = height;
        }

        inline T GetTop() const
        {
            return Y;
        }

        inline T GetBottom() const
        {
            return Y + Height;
        }

        inline T GetLeft() const
        {
            return X;
        }

        inline T GetRight() const
        {
            return X + Width;
        }

        inline Vector2f GetPosition() const
        {
            return Vector2f(X, Y);
        }

        inline Vector2f GetSize() const
        {
            return Vector2f(Width, Height);
        }

        inline bool Contains(const Vector2f& vector) const
        {
            return (vector.X >= X) && (vector.X <= GetRight()) && (vector.Y >= Y) && (vector.Y <= GetBottom());
        }

        inline bool CompletelyContains(const Vector2f& vector) const
        {
            return (vector.X > X) && (vector.X < GetRight()) && (vector.Y > Y) && (vector.Y < GetBottom());
        }

        inline bool Contains(const Rectangle<T>& rect) const
        {
            return (X <= rect.X) && (GetRight() >= rect.GetRight()) && (Y <= rect.Y) && (GetBottom() >= rect.GetBottom());
        }

        inline bool CompletelyContains(const Rectangle<T>& rect) const
        {
            return (X < rect.X) && (GetRight() > rect.GetRight()) && (Y < rect.Y) && (GetBottom() > rect.GetBottom());
        }

        inline bool Intersects(const Rectangle<T>& rect) const
        {
            return (X < rect.GetRight()) && (GetRight() > rect.GetLeft()) && (Y < rect.GetBottom()) && (GetBottom() > rect.Y);
        }

        inline bool IntersectsOrTouches(const Rectangle<T>& rect) const
        {
            return (X <= rect.GetRight()) && (GetRight() >= rect.GetLeft()) && (Y <= rect.GetBottom()) && (GetBottom() >= rect.Y);
        }

        inline bool Equals(const Rectangle<T>& rect) const
        {
            return (X == rect.X) && (Y == rect.Y) && (Width == rect.Width) && (Height == rect.Height);
        }

        inline void operator+=(const Rectangle<T>& rect) noexcept
        {
            X = std::min(X, rect.X);
            Y = std::min(Y, rect.Y);
            Width = std::max(GetRight() - X, rect.GetRight() - X);
            Height = std::max(GetBottom() - Y, rect.GetBottom() - Y);
        }
    };

    typedef Rectangle<float> Rectanglef;
}

template <class T>
std::ostream& operator <<(std::ostream& out, const FaceEngine::Rectangle<T>& rect);

template <class T>
FaceEngine::Rectangle<T> operator+(const FaceEngine::Rectangle<T>& firstRect, const FaceEngine::Rectangle<T>& secondRect) noexcept;

template <class T>
bool operator==(const FaceEngine::Rectangle<T>& firstRect, const FaceEngine::Rectangle<T>& secondRect) noexcept;

template <class T>
bool operator!=(const FaceEngine::Rectangle<T>& firstRect, const FaceEngine::Rectangle<T>& secondRect) noexcept;

#endif