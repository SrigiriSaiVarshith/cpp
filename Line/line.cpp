#include "tgaimage.h"
#include <cmath>

constexpr TGAColor white = {255, 255, 255, 255};
constexpr TGAColor green = {0, 255, 0, 255};
constexpr TGAColor red = {0, 0, 255, 255};
constexpr TGAColor blue = {255, 128, 64, 255};
constexpr TGAColor yellow = {0, 200, 255, 255};

void Draw_line(int ax, int ay, int bx, int by, TGAImage &image)
{
    float dist = sqrt(pow((ax - bx), 2) + pow((ay - by), 2));
    dist = ceil(dist);
    for (int i = 0; i <= dist; i++)
    {
        double t = (double)i / dist;
        int cx = ax + t * (bx - ax);
        int cy = ay + t * (by - ay);
        image.set(cx, cy, white);
    }
}

int main(int argc, char **argv)
{
    constexpr int width = 64;
    constexpr int height = 64;
    TGAImage framebuffer(width, height, TGAImage::RGB);

    int ax = 7, ay = 3;
    int bx = 12, by = 37;

    framebuffer.set(ax, ay, white);
    framebuffer.set(bx, by, white);

    Draw_line(ax, ay, bx, by, framebuffer);

    framebuffer.write_tga_file("line.tga");
    return 0;
}
