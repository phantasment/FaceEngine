#ifndef FACEENGINE_EXCEPTION_H_
#define FACEENGINE_EXCEPTION_H_

#include <string>
#include <iostream>

#include "FaceEngine/OGL.h"

namespace FaceEngine
{
    class Exception
    {
    private:
        std::string origin;
        std::string msg;

        inline Exception(const std::string& o, const std::string& m) noexcept
        {
            origin = o;
            msg = m;
        }
    public:
        inline const std::string GetMessage() const noexcept
        {
            if (origin.empty())
            {
                return msg;
            }
            else
            {
                return '[' + origin + "]: " + msg;
            }
        }

        static inline Exception FromMessage(const std::string& msg) noexcept
        {
            return Exception("", msg);
        }

        static inline Exception FromMessage(const std::string& origin, const std::string& msg) noexcept
        {
            return Exception(origin, msg);
        }
    };

    std::ostream& operator<<(std::ostream&, const Exception&);
}

#endif