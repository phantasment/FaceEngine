#ifndef FACEENGINE_AUDIODEVICE_H_
#define FACEENGINE_AUDIODEVICE_H_

#include "FaceEngine/Exception.h"
#include "FaceEngine/OAL.h"

namespace FaceEngine
{
    class AudioDevice
    {
    friend class Game;
    private:
        bool active;
        ALCdevice* alDevice;
        ALCcontext* alContext;
        AudioDevice();
        ~AudioDevice();
    public:
        inline bool IsActive() const noexcept { return active; }
    };
}

#endif