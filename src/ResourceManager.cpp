#include "FaceEngine/ResourceManager.h"

namespace FaceEngine
{
    void ResourceManager::AddResource(Resource* res)
    {
        resources.push_back(res);
    }

    void ResourceManager::MarkResource(Resource* res)
    {
        marked.push_back(res);
    }

    void ResourceManager::DisposeResource(Resource* res)
    {
        std::vector<FaceEngine::Resource*>::iterator it = resources.begin();

        while (it != resources.end())
        {
            if (*it == res)
            {
                resources.erase(it);
                Resource* r = *it;
                r->Dispose();
                delete r;
                return;
            }
        }
    }

    void ResourceManager::DisposeAllResources()
    {
        HandleMarked();

        for (Resource* res : resources)
        {
            res->Dispose();
            delete res;
        }

        resources.clear();
    }

    void ResourceManager::HandleMarked()
    {
        bool deleted;
        std::size_t amt = marked.size() < 10 ? marked.size() : 10;

        for (std::size_t i = 0; i < amt; ++i)
        {
            Resource* res = marked[i];
            deleted = false;
            res->Dispose();
            delete res;
            std::vector<FaceEngine::Resource*>::iterator it = resources.begin();

            while (!deleted && it != resources.end())
            {
                if (*it == res)
                {
                    deleted = true;
                    resources.erase(it);
                }
            }
        }

        marked.clear();
    }
}