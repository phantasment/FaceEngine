#include <iostream>

#include "FaceEngine/Math.h"

int main()
{
    FaceEngine::Vector4f vec4;
    std::cout << vec4 << "\n\n";

    FaceEngine::Matrix4f mat4;
    std::cout << mat4 << '\n';
    mat4.Identity();
    std::cout << mat4 << '\n';
    return 0;
}