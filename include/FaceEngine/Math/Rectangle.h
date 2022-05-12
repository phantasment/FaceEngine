#ifndef FACEENGINE_MATH_RECTANGLE_H_
#define FACEENGINE_MATH_RECTANGLE_H_

#include "FaceEngine/Math/Vector2.h"
#include <iostream>

namespace FaceEngine
{
    template <typename T>
    class Rectangle
    {
        static_assert(std::is_same<float, T>() || 
                      std::is_same<int, T>() || 
                      std::is_same<double, T>() || 
                      std::is_same<short, T>() ||
                      std::is_same<long, T>());

    public:
        T X;
        T Y;
        T Width;
        T Height;

        Rectangle<T>();
        Rectangle<T>(const Vector2f& position, const T width, const T height);
        Rectangle<T>(const T x, const T y, const T width, const T height);

        T GetTop() const;
        T GetBottom() const;
        T GetLeft() const;
        T GetRight() const;

        Vector2f GetPosition() const;
        Vector2f GetSize() const;

        bool Contains(const Vector2f& vector) const;
        bool CompletelyContains(const Vector2f& vector) const;
        bool Contains(const Rectangle<T>& rect) const;
        bool CompletelyContains(const Rectangle<T>& rect) const;
        bool Intersects(const Rectangle<T>& rect) const;
        bool IntersectsOrTouches(const Rectangle<T>& rect) const;
        bool Equals(const Rectangle<T>& rect) const;

        void operator +=(const Rectangle<T>& rect) noexcept;
    };
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