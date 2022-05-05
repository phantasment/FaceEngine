#include "FaceEngine/Math/Rectangle.h"
#include <cmath>

namespace FaceEngine
{
    template <typename T>
    Rectangle<T>::Rectangle()
    {
        X = 0;
        Y = 0;
        Width = 0;
        Height = 0;
    }

    template <typename T>
    Rectangle<T>::Rectangle(const Vector2f& position, const T width, const T height)
    {
        X = position.X;
        Y = position.Y;
        Width = width;
        Height = height;
    }

    template <typename T>
    Rectangle<T>::Rectangle(const T x, const T y, const T width, const T height)
    {
        X = x;
        Y = y;
        Width = width;
        Height = height;
    }

    template <typename T>
    T Rectangle<T>::GetTop() const
    {
        return Y;
    }

    template <typename T>
    T Rectangle<T>::GetBottom() const
    {
        return Y + Height;
    }

    template <typename T>
    T Rectangle<T>::GetLeft() const
    {
        return X;
    }

    template <typename T>
    T Rectangle<T>::GetRight() const
    {
        return X + Width;
    }

    template <typename T>
    Vector2f Rectangle<T>::GetPosition() const
    {
        return Vector2f(X, Y);
    }

    template <typename T>
    Vector2f Rectangle<T>::GetSize() const
    {
        return Vector2f(Width, Height);
    }

    template <typename T>
    bool Rectangle<T>::Contains(const Vector2f& vector) const
    {
        return (vector.X >= X) && (vector.X <= GetRight()) && (vector.Y >= Y) && (vector.Y <= GetBottom());
    }

    template <typename T>
    bool Rectangle<T>::CompletelyContains(const Vector2f& vector) const
    {
        return (vector.X > X) && (vector.X < GetRight()) && (vector.Y > Y) && (vector.Y < GetBottom());
    }

    template <typename T>
    bool Rectangle<T>::Contains(const Rectangle<T>& rect) const
    {
        return (X <= rect.X) && (GetRight() >= rect.GetRight()) && (Y <= rect.Y) && (GetBottom() >= rect.GetBottom());
    }

    template <typename T>
    bool Rectangle<T>::CompletelyContains(const Rectangle<T>& rect) const
    {
        return (X < rect.X) && (GetRight() > rect.GetRight()) && (Y < rect.Y) && (GetBottom() > rect.GetBottom());
    }

    template <typename T>
    bool Rectangle<T>::Intersects(const Rectangle<T>& rect) const
    {
        return (X < rect.GetRight()) && (GetRight() > rect.GetLeft()) && (Y < rect.GetBottom()) && (GetBottom() > rect.Y);
    }

    template <typename T>
    bool Rectangle<T>::IntersectsOrTouches(const Rectangle<T>& rect) const
    {
        return (X <= rect.GetRight()) && (GetRight() >= rect.GetLeft()) && (Y <= rect.GetBottom()) && (GetBottom() >= rect.Y);
    }

    template <typename T>
    bool Rectangle<T>::Equals(const Rectangle<T>& rect) const
    {
        return (X == rect.X) && (Y == rect.Y) && (Width == rect.Width) && (Height == rect.Height);
    }

    template <typename T>
    void Rectangle<T>::operator+=(const Rectangle<T>& rect) noexcept
    {
        X = std::min(X, rect.X);
        Y = std::min(Y, rect.Y);
        Width = std::max(GetRight() - X, rect.GetRight() - X);
        Height = std::max(GetBottom() - Y, rect.GetBottom() - Y);
    }
}

template <typename T>
FaceEngine::Rectangle<T> operator+(const FaceEngine::Rectangle<T>& firstRect, const FaceEngine::Rectangle<T>& secondRect) noexcept
{
    float X = std::min(firstRect.X, secondRect.X);
    float Y = std::min(firstRect.Y, secondRect.Y);

    FaceEngine::Rectangle rect = FaceEngine::Rectangle(X, Y, 
                                                       std::max(firstRect.GetRight() - X, secondRect.GetRight() - X), 
                                                       std::max(firstRect.GetBottom() - Y, secondRect.GetBottom() - Y));
}

template <typename T>
bool operator==(const FaceEngine::Rectangle<T>& firstRect, const FaceEngine::Rectangle<T>& secondRect) noexcept
{
    return firstRect.Equals(secondRect);
}

template <typename T>
bool operator!=(const FaceEngine::Rectangle<T>& firstRect, const FaceEngine::Rectangle<T>& secondRect) noexcept
{
    return !firstRect.Equals(secondRect);
}

template <typename T>
std::ostream& operator <<(std::ostream& out, const FaceEngine::Rectangle<T>& rect)
{
    return out << "Rectangle:[X: " << rect.X << ", Y: " << rect.Y << ", Width: " << rect.Width << ", Height: " << rect.Height;
}