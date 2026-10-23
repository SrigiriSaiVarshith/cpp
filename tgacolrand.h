#include<cstdlib>
#include<random>
#include "tgaimage.h"

TGAColor RandColour()
{
    static std::random_device rd;
    static std::mt19937 rng(rd());
    static std::uniform_int_distribution<int> dist(0,255);

    return TGAColor{
        static_cast<std::uint8_t>(dist(rng)),
        static_cast<std::uint8_t>(dist(rng)),
        static_cast<std::uint8_t>(dist(rng)),
        255

    };
}
