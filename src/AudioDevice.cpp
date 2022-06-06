#include "FaceEngine/AudioDevice.h"

namespace FaceEngine
{
    AudioDevice::AudioDevice()
    {
        active = false;
        alDevice = alcOpenDevice(nullptr);

        if (!alDevice)
        {
            return;
        }

        alContext = alcCreateContext(alDevice, nullptr);

        if (!alcMakeContextCurrent(alContext))
        {
            alcDestroyContext(alContext);
            alcCloseDevice(alDevice);
            return;
        }

        active = true;
    }

    AudioDevice::~AudioDevice()
    {
        if (active)
        {
            alcDestroyContext(alContext);
            alcCloseDevice(alDevice);
        }
    }
}