#ifndef FACEENGINE_AUDIODEVICE_H_
#define FACEENGINE_AUDIODEVICE_H_

#include "FaceEngine/Resource.h"
#include "FaceEngine/Exception.h"
#include "FaceEngine/OAL.h"

namespace FaceEngine
{
    class AudioDevice : public Resource
    {
    friend class Game;
    private:
        bool active;
        ALCdevice* alDevice;
        ALCcontext* alContext;
        AudioDevice();
    public:
        inline bool IsDisposed() noexcept override { return !active; }

        void Dispose() noexcept override;

        inline bool IsActive() const noexcept { return active; }
    };
}

#endif