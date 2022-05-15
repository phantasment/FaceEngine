#ifndef FACEENGINE_RESOURCE_H_
#define FACEENGINE_RESOURCE_H_

namespace FaceEngine
{
    /**
     * @brief A class representing a Face Engine resource.
     * 
     * Resources in Face Engine typically inherit this class and can be automatically managed by the ResourceManager class.
     * IsDisposed should return a boolean value indicating whether the resource has been disposed.
     * Dispose should contain code that should be executed before a resource is deleted from memory.
     * To give a Resource object automatic deallocation upon game exit, use ResourceManager::TrackResource(Resource*).
     * To remove automatic deallocation from a Resource object, use ResourceManager::UntrackResource(Resource*).
     * To dispose of a resource that is being tracked, use ResourceManager::DisposeResource(Resource*).
     * Resources that are being tracked by the ResourceManager should not be deleted or disposed of manually.
     */
    class Resource
    {
    public:
        /**
         * @brief Returns a boolean value indicating whether this resource has been disposed.
         * 
         * If a resource has been disposed it can be safely deleted from memory.
         * A disposed object generally cannot be reused.
         * This function must not throw an exception.
         * @return true If the resource has been disposed.
         * @return false If the resource has not been disposed.
         */
        virtual const bool IsDisposed() noexcept;

        /**
         * @brief Code to run before a Resource is deleted from memory (generally cleanup code).
         * 
         * Other resources can be disposed of in this function using ResourceManager::DisposeResource(Resource*).
         * If a resource has been disposed it can be safely deleted from memory.
         * A disposed object generally cannot be reused.
         * This function must not throw an exception.
         */
        virtual void Dispose() noexcept;
    };
}

#endif