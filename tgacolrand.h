/* Made a Random colour generator*/

#include<cstdlib>
#include<random>
#include "tgaimage.h"

TGAColor RandColour()
{
    static std::random_device rd;//Use hardware entropy for a seed-gen (eg: CPU noise)
    static std::mt19937 rng(rd());//With the seed from rd(), mt19937 generate a random number from 0 to 2^19937-1
    static std::uniform_int_distribution<int> dist(0,255);//Limiting the numbers to 0 to 255(inclusive)

    return TGAColor{
        static_cast<std::uint8_t>(dist(rng)),
        static_cast<std::uint8_t>(dist(rng)),
        static_cast<std::uint8_t>(dist(rng)),
        255

    };//returns something like {0,0,124,255}(This is just an example)
}
