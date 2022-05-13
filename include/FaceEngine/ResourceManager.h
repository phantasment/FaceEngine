#ifndef FACEENGINE_RESOURCEMANAGER_H_
#define FACEENGINE_RESOURCEMANAGER_H_

#include <set>
#include <cstdint>

#include "FaceEngine/Resource.h"

namespace FaceEngine
{
    class ResourceManager
    {
    private:
        std::set<Resource*> resources;
        bool disposingAll;
    public:
        inline ResourceManager()
        {
            disposingAll = false;
        }

        bool TrackResource(Resource*);
        bool UntrackResource(Resource*);
        bool DisposeResource(Resource*);
        void DisposeAllResources();
    };
}

#endif