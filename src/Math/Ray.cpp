#include "FaceEngine/Math/Ray.h"

namespace FaceEngine
{
    Ray::Ray(const Vector3f& position, const Vector3f& direction) noexcept
    {
        Position = Vector3f(position.X, position.Y, position.Z);
        Direction = Vector3f(direction.X, direction.Y, direction.Z);
    }

    bool Ray::Equals(const Ray& ray) const noexcept
    {
        return ray.Position == Position && ray.Direction == Direction;
    }

    std::string Ray::ToString() const noexcept
    {
        return "Ray:[Position" + Position.ToStringWithoutHead() + ", Direction" + Direction.ToStringWithoutHead() + "]"; 
    }
}

bool operator==(const FaceEngine::Ray& firstRay, const FaceEngine::Ray& secondRay) noexcept
{
    return firstRay.Equals(secondRay);
}

bool operator!=(const FaceEngine::Ray& firstRay, const FaceEngine::Ray& secondRay) noexcept
{
    return !firstRay.Equals(secondRay);
}