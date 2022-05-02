#ifndef FACEENGINE_RESOURCE_H_
#define FACEENGINE_RESOURCE_H_

namespace FaceEngine
{
    class Resource
    {
    public:
        virtual const bool IsDisposed() noexcept;
        virtual void Dispose() noexcept;
    };
}

#endif