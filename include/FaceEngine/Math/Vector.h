#ifndef FACEENGINE_MATH_VECTOR_H_
#define FACEENGINE_MATH_VECTOR_H_

#include <vector>

#include "FaceEngine/Exception.h"

namespace FaceEngine
{
    class Vector
    {
    public:
        virtual const std::vector<float> ToArray() const noexcept;
    };
}

#endif