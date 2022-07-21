#include "FaceEngine/Graphics/Colour.h"
#include <sstream>
#include <ios>
#include <cmath>
#include <iostream>

namespace FaceEngine
{
    FaceEngine::Colour::Colour()
    {
        R = 1;
        G = 1;
        B = 1;
        A = 1;
    }

    FaceEngine::Colour::Colour(float r, float g, float b)
    {
        R = r;
        G = g;
        B = b;
        A = 1;
    }

    FaceEngine::Colour::Colour(float r, float g, float b, float a)
    {
        R = r;
        G = g;
        B = b;
        A = a;
    }

    FaceEngine::Colour::~Colour()
    {

    }

    FaceEngine::Colour FaceEngine::Colour::CreateFromRGB(int r, int g, int b)
    {
        return FaceEngine::Colour(r / 255.0, g / 255.0, b / 255.0);
    }

    float FaceEngine::Colour::GetR() const
    {
        return R;
    }

    float FaceEngine::Colour::GetG() const
    {
        return G;
    }

    float FaceEngine::Colour::GetB() const
    {
        return B;
    }

    float FaceEngine::Colour::GetA() const
    {
        return A;
    }

    int FaceEngine::Colour::GetRAsInt() const
    {
        return (int)((R * 255) + 0.5);
    }

    int FaceEngine::Colour::GetGAsInt() const
    {
        return (int)((G * 255) + 0.5);
    }

    int FaceEngine::Colour::GetBAsInt() const
    {
        return (int)((B * 255) + 0.5);
    }

    int FaceEngine::Colour::GetAAsInt() const
    {
        return (int)((A * 255) + 0.5);
    }

    int FaceEngine::Colour::GetHue() const
    {
        float max = std::max(std::max(R, G), B);
        float min = std::min(std::min(R, G), B);

        if (max == 0 && min == 0)
        {
            return 0;
        }

        float delta = max - min;

        if (max == R)
        {
            return (int)std::round(60 * ((G - B) / delta) + 360) % 360;
        }
        else if (max == G)
        {
            return (int)std::round(60 * ((B - R) / delta) + 120) % 360;
        }
        else
        {
            return (int)std::round(60 * ((R - G) / delta) + 240) % 360;
        }
    }

    float FaceEngine::Colour::GetHSVSaturation() const
    {
        float max = std::max(std::max(R, G), B);
        float delta = max - std::min(std::min(R, G), B);

        if (delta == 0)
        {
            return 0;
        }

        return delta / max;
    }

    float FaceEngine::Colour::GetHSVValue() const
    {
        return std::max(std::max(R, G), B);
    }

    float FaceEngine::Colour::GetHSLSaturation() const
    {
        float delta = std::max(std::max(R, G), B) - std::min(std::min(R, G), B);

        if (delta == 0)
        {
            return 0;
        }

        return delta / (1 - std::abs(2 * GetHSLLuminance() - 1));
    }

    float FaceEngine::Colour::GetHSLLuminance() const
    {
        float max = std::max(std::max(R, G), B);
        float min = std::min(std::min(R, G), B);

        return (max + min) / 2;
    }

    std::string FaceEngine::Colour::GetHex(bool includeHead) const
    {
        std::stringstream ss;

        if (includeHead)
        {
            ss << "#";
        }

        ss << std::hex << (int)std::round(R * 255);
        ss << std::hex << (int)std::round(G * 255);
        ss << std::hex << (int)std::round(B * 255);

        return ss.str();
    }

    void FaceEngine::Colour::SetR(float r)
    {
        R = r;
    }

    void FaceEngine::Colour::SetG(float g)
    {
        G = g;
    }

    void FaceEngine::Colour::SetB(float b)
    {
        B = b;
    }

    void FaceEngine::Colour::SetA(float a)
    {
        A = a;
    }

    void FaceEngine::Colour::SetRAsInt(int r)
    {
        R = r / 255.0;
    }

    void FaceEngine::Colour::SetGAsInt(int g)
    {
        G = g / 255.0;
    }

    void FaceEngine::Colour::SetBAsInt(int b)
    {
        B = b / 255.0;
    }

    void FaceEngine::Colour::SetAAsInt(int a)
    {
        A = a / 255.0;
    }

    void FaceEngine::Colour::SetRGB(float r, float g, float b, float a)
    {
        R = r;
        G = g;
        B = b;
        A = a;
    }

    void FaceEngine::Colour::SetRGB(int r, int g, int b, int a)
    {
        R = r / 255.0;
        G = g / 255.0;
        B = b / 255.0;
        A = a / 255.0;
    }

    void FaceEngine::Colour::SetHSV(int hue, float saturation, float value, float opacity)
    {
        float c = value * saturation;
        float x = c * (1 - std::abs(((hue / 60) % 2) - 1));
        float m = value - c;

        float r = m;
        float g = m;
        float b = m;

        if (hue < 60)
        {
            r += c;
            g += x;
        }
        else if (hue < 120)
        {
            r += x;
            g += c;
        }
        else if (hue < 180)
        {
            g += c;
            b += x;
        }
        else if (hue < 240)
        {
            g += x;
            b += c;
        }
        else if (hue < 300)
        {
            r += x;
            b += c;
        }
        else if (hue < 360)
        {
            r += c;
            b += x;
        }

        R = r;
        G = g;
        B = b;
        A = opacity;
    }

    void FaceEngine::Colour::Add(FaceEngine::Colour& foreground)
    {
        FaceEngine::Colour temp = FaceEngine::Colour(R, G, B, A); 

        A = 1 - ((1 - foreground.A) * (1 - A));

        if (A != 0)
        {
            float foregroundAlphaRatio = temp.A / A;
            float backgroundAlphaRatio = temp.A * (1 - foreground.A) / A;

            R = (foreground.R * foregroundAlphaRatio) + (temp.R * backgroundAlphaRatio);
            B = (foreground.B * foregroundAlphaRatio) + (temp.B * backgroundAlphaRatio);
            G = (foreground.G * foregroundAlphaRatio) + (temp.G * backgroundAlphaRatio);
        }
    }

    FaceEngine::Colour FaceEngine::Colour::Lerp(const FaceEngine::Colour& startColour, const FaceEngine::Colour& endColour, float t)
    {
        return Colour(startColour.R + (endColour.R - startColour.R) * t,
                    startColour.G + (endColour.G - startColour.G) * t,
                    startColour.B + (endColour.B - startColour.B) * t,
                    startColour.A + (endColour.A - startColour.A) * t);
    }

    void FaceEngine::Colour::Print() const
    {
        std::cout << "Colour:[R: " << R << ", G: " << G << ", B: " << B << ", A: " << A << "]";
    }

    const FaceEngine::Colour FaceEngine::Colour::Black = FaceEngine::Colour(0, 0, 0);
    const FaceEngine::Colour FaceEngine::Colour::White = FaceEngine::Colour(1, 1, 1);
    const FaceEngine::Colour FaceEngine::Colour::Red = FaceEngine::Colour(1, 0, 0);
    const FaceEngine::Colour FaceEngine::Colour::Orange = FaceEngine::Colour(1, 0.5, 0);
    const FaceEngine::Colour FaceEngine::Colour::Yellow = FaceEngine::Colour(1, 1, 0);
    const FaceEngine::Colour FaceEngine::Colour::Lime = FaceEngine::Colour(0.5, 1, 0);
    const FaceEngine::Colour FaceEngine::Colour::Green = FaceEngine::Colour(0, 1, 0);
    const FaceEngine::Colour FaceEngine::Colour::Cyan = FaceEngine::Colour(0, 1, 1);
    const FaceEngine::Colour FaceEngine::Colour::LightBlue = FaceEngine::Colour(0, 0.5, 1);
    const FaceEngine::Colour FaceEngine::Colour::Blue = FaceEngine::Colour(0, 0, 1);
    const FaceEngine::Colour FaceEngine::Colour::Magenta = FaceEngine::Colour(1, 0, 1);
}

std::ostream& operator<<(std::ostream& os, const FaceEngine::Colour& c) noexcept
{
    os << '[' << c.GetRAsInt() << ", " << c.GetGAsInt() << ", " << c.GetBAsInt() << ", " << c.GetAAsInt() << ']';
    return os;
}

bool operator ==(const FaceEngine::Colour& firstColour, const FaceEngine::Colour& secondColour) noexcept
{
    return firstColour.GetR() == secondColour.GetR() &&
           firstColour.GetG() == secondColour.GetG() &&
           firstColour.GetB() == secondColour.GetB() &&
           firstColour.GetA() == secondColour.GetA();
}

bool operator !=(const FaceEngine::Colour& firstColour, const FaceEngine::Colour& secondColour) noexcept
{
    return firstColour.GetR() != secondColour.GetR() ||
           firstColour.GetG() != secondColour.GetG() ||
           firstColour.GetB() != secondColour.GetB() ||
           firstColour.GetA() != secondColour.GetA();
}