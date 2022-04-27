#ifndef FACEENGINE_MATH_VECTOR4F_H_
#define FACEENGINE_MATH_VECTOR4F_H_

#include "FaceEngine/Math/Vector.h"

namespace FaceEngine
{
    class Vector4f : public Vector
    {
    private:
        float data[4];
    public:
        Vector4f();

        const std::vector<float> ToArray() const noexcept override;
    };
}

#endif