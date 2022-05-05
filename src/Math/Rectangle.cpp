#include "FaceEngine/Math/Rectangle.h"
#include <cmath>

namespace FaceEngine
{
    Rectangle::Rectangle()
    {
        X = 0;
        Y = 0;
        Width = 0;
        Height = 0;
    }

    Rectangle::Rectangle(const Vector2f& position, const float& width, const float& height)
    {
        X = position.X;
        Y = position.Y;
        Width = width;
        Height = height;
    }

    Rectangle::Rectangle(const float& x, const float& y, const float& width, const float& height)
    {
        X = x;
        Y = y;
        Width = width;
        Height = height;
    }

    float Rectangle::GetTop() const
    {
        return Y;
    }

    float Rectangle::GetBottom() const
    {
        return Y + Height;
    }

    float Rectangle::GetLeft() const
    {
        return X;
    }

    float Rectangle::GetRight() const
    {
        return X + Width;
    }

    Vector2f Rectangle::GetPosition() const
    {
        return Vector2f(X, Y);
    }

    Vector2f Rectangle::GetSize() const
    {
        return Vector2f(Width, Height);
    }

    bool Rectangle::Contains(const Vector2f& vector) const
    {
        return (vector.X >= X) && (vector.X <= GetRight()) && (vector.Y >= Y) && (vector.Y <= GetBottom());
    }

    bool Rectangle::CompletelyContains(const Vector2f& vector) const
    {
        return (vector.X > X) && (vector.X < GetRight()) && (vector.Y > Y) && (vector.Y < GetBottom());
    }

    bool Rectangle::Contains(const Rectangle& rect) const
    {
        return (X <= rect.X) && (GetRight() >= rect.GetRight()) && (Y <= rect.Y) && (GetBottom() >= rect.GetBottom());
    }

    bool Rectangle::CompletelyContains(const Rectangle& rect) const
    {
        return (X < rect.X) && (GetRight() > rect.GetRight()) && (Y < rect.Y) && (GetBottom() > rect.GetBottom());
    }

    bool Rectangle::Intersects(const Rectangle& rect) const
    {
        return (X < rect.GetRight()) && (GetRight() > rect.GetLeft()) && (Y < rect.GetBottom()) && (GetBottom() > rect.Y);
    }

    bool Rectangle::IntersectsOrTouches(const Rectangle& rect) const
    {
        return (X <= rect.GetRight()) && (GetRight() >= rect.GetLeft()) && (Y <= rect.GetBottom()) && (GetBottom() >= rect.Y);
    }

    bool Rectangle::Equals(const Rectangle& rect) const
    {
        return (X == rect.X) && (Y == rect.Y) && (Width == rect.Width) && (Height == rect.Height);
    }

    void Rectangle::operator+=(const Rectangle& rect) noexcept
    {
        X = std::min(X, rect.X);
        Y = std::min(Y, rect.Y);
        Width = std::max(GetRight() - X, rect.GetRight() - X);
        Height = std::max(GetBottom() - Y, rect.GetBottom() - Y);
    }
}

FaceEngine::Rectangle operator+(const FaceEngine::Rectangle& firstRect, const FaceEngine::Rectangle& secondRect) noexcept
{
    float X = std::min(firstRect.X, secondRect.X);
    float Y = std::min(firstRect.Y, secondRect.Y);

    FaceEngine::Rectangle rect = FaceEngine::Rectangle(X, Y, 
                                                       std::max(firstRect.GetRight() - X, secondRect.GetRight() - X), 
                                                       std::max(firstRect.GetBottom() - Y, secondRect.GetBottom() - Y));
}

bool operator==(const FaceEngine::Rectangle& firstRect, const FaceEngine::Rectangle& secondRect) noexcept
{
    return firstRect.Equals(secondRect);
}

bool operator!=(const FaceEngine::Rectangle& firstRect, const FaceEngine::Rectangle& secondRect) noexcept
{
    return !firstRect.Equals(secondRect);
}

std::ostream& operator <<(std::ostream& out, const FaceEngine::Rectangle& rect)
{
    return out << "Rectangle:[X: " << rect.X << ", Y: " << rect.Y << ", Width: " << rect.Width << ", Height: " << rect.Height;
}