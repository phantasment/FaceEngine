#include "FaceEngine/Resource.h"

namespace FaceEngine
{
    bool Resource::IsDisposed() noexcept { return true; }

    void Resource::Dispose() noexcept { }
}