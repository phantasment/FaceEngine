#ifndef FACEENGINE_COLOUR_H
#define FACEENGINE_COLOUR_H

#include <string>
#include <iostream>

#include "FaceEngine/Math/Vector3.h"
#include "FaceEngine/Math/Vector4.h"

namespace FaceEngine
{
    class Colour
    {
    private:
        float R;
        float G;
        float B;
        float A;

    public:
        // ----- Constuctors and Destructors -----

        Colour();
        Colour(float r, float g, float b);
        Colour(float r, float g, float b, float a);
        ~Colour();

        // ----- Factory Methods -----

        static Colour CreateFromRGB(int r, int g, int b);
        static Colour CreateFromHSL(int h, float s, float l);
        static Colour CreateFromHSV(int h, float s, float v);

        // ----- Getters -----

        float GetR() const;
        float GetG() const;
        float GetB() const;
        float GetA() const;

        int GetRAsInt() const;
        int GetGAsInt() const;
        int GetBAsInt() const;
        int GetAAsInt() const;

        int GetHue() const;
        float GetHSVSaturation() const;
        float GetHSVValue() const;
        float GetHSLSaturation() const;
        float GetHSLLuminance() const;

        std::string GetHex(bool includeHead = true) const;

        // ----- Setters -----

        void SetR(float r);
        void SetG(float g);
        void SetB(float b);
        void SetA(float a);

        void SetRAsInt(int r);
        void SetGAsInt(int g);
        void SetBAsInt(int b);
        void SetAAsInt(int a);

        void SetRGB(float r, float g, float b, float a);
        void SetRGB(int r, int g, int b, int a);
        void SetHSV(int hue, float saturation, float value, float opacity);
        void SetHSL(int hue, float saturation, float lightness, float opacity);
        void SetHex(std::string hex);

        // ----- Conversions -----

        FaceEngine::Vector3f ToVector3() const;
        FaceEngine::Vector4f ToVector4() const;
        FaceEngine::Vector3f ToVector3RGB() const;
        FaceEngine::Vector4f ToVector4RGB() const;
        FaceEngine::Vector3f ToVector3HSV() const;
        FaceEngine::Vector4f ToVector4HSV() const;
        FaceEngine::Vector3f ToVector3HSL() const;
        FaceEngine::Vector4f ToVector4HSL() const;

        std::string ToString() const;
        std::string ToStringRGB() const;
        std::string ToStringHSV() const;
        std::string ToStringHSL() const;

        // ----- Operations -----

        void Add(Colour& foreground);
        void Subtract(Colour& colour);
        bool Equals(Colour& colour) const;
        void Print() const;

        // ----- Operators -----

        void operator +=(Colour& colour);
        void operator -=(Colour& colour);

        // ----- Static Operations -----

        static Colour Add(Colour& firstColour, Colour& secondColour);
        static Colour Subtract(Colour& firstColour, Colour& secondColour);
        static bool Equals(Colour& firstColour, Colour& secondColour);
        static Colour Lerp(const Colour& startColour, const Colour& endColour, float t);

        // ----- Colour Presets -----

        static const Colour Black;
        static const Colour White;
        static const Colour Red;
        static const Colour Orange;
        static const Colour Yellow;
        static const Colour Lime;
        static const Colour Green;
        static const Colour Cyan;
        static const Colour LightBlue;
        static const Colour Blue;
        static const Colour Magenta;
    };
}

std::ostream& operator<<(std::ostream& os, const FaceEngine::Colour& c) noexcept;

FaceEngine::Colour operator +(FaceEngine::Colour& firstColour, FaceEngine::Colour& secondColour);
FaceEngine::Colour operator -(FaceEngine::Colour& firstColour, FaceEngine::Colour& secondColour);

bool operator ==(FaceEngine::Colour& firstColour, FaceEngine::Colour& secondColour) noexcept;
bool operator !=(FaceEngine::Colour& firstColour, FaceEngine::Colour& secondColour) noexcept;

#endif