#ifndef FACEENGINE_MATH_MATRIX_H_
#define FACEENGINE_MATH_MATRIX_H_

#include <vector>

#include "FaceEngine/Exception.h"

namespace FaceEngine
{
    class Matrix
    {
    public:
        virtual const std::vector<float> ToArray() const noexcept;
    };
}

#endif