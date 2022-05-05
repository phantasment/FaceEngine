#ifndef FACEENGINE_MATH_RAY_H_
#define FACEENGINE_MATH_RAY_H_

#include "FaceEngine/Math/Vector3f.h"

namespace FaceEngine
{
    class Ray
    {
    public:
        Vector3f Position;
        Vector3f Direction;

        Ray(const Vector3f& position, const Vector3f& direction) noexcept;

        bool Equals(const Ray& ray) const noexcept;
        std::string ToString() const noexcept;
    };
}

bool operator==(const FaceEngine::Ray& firstRay, const FaceEngine::Ray& secondRay) noexcept;
bool operator!=(const FaceEngine::Ray& firstRay, const FaceEngine::Ray& secondRay) noexcept;

#endif