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
        ALCdevice* alDevice;
        ALCcontext* alContext;
        AudioDevice();
        ~AudioDevice();
    };
}

#endif