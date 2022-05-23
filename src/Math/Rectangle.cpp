#include "FaceEngine/Math/Rectangle.h"
#include <cmath>

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