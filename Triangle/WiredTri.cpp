#include <tgaimage.h>
#include <algorithm>
#include <cmath>
#include <utility>

constexpr TGAColor white = {255, 255, 255, 255};

/*You can use your own values or take input using cin*/
float bc_thick = 20.0f;
float ca_thick = 6.0f;
float ab_thick =55.0f;

int CalcArea(int ax, int ay, int bx, int by, int cx, int cy)
{
    return (by - ay) * (bx + ax) + (cy - by) * (cx + bx) + (ay - cy) * (ax + cx);
}

/* Bresenhams Line Algo. Learned it from "NoBS Code" channel. He explained it very well
    and how to cover all the 8-octants*/

void drawlineH(int ax, int ay, int bx, int by, TGAImage &image)
{
    if (ax > bx)
    {
        std::swap(ax, bx);
        std::swap(ay, by);
    }
    int dx = bx - ax;
    int dy = by - ay;

    int dir = (dy < 0) ? -1 : 1;
    dy *= dir;

    int D = 2 * dy - dx;
    int y = ay;

    for (int i = 0; i <= dx; i++)
    {
        image.set(ax + i, y, white);
        if (D > 0)
        {
            y += dir;
            D = D + 2 * dy - 2 * dx;
        }
        else
        {
            D = D + 2 * dy;
        }
    }
}

void drawlineV(int ax, int ay, int bx, int by, TGAImage &image)
{
    if (ay > by)
    {
        std::swap(ax, bx);
        std::swap(ay, by);
    }
    int dx = bx - ax;
    int dy = by - ay;

    int dir = (dx < 0) ? -1 : 1;
    dx *= dir;

    int D = 2 * dx - dy;
    int x = ax;

    for (int i = 0; i <= dy; i++)
    {
        image.set(x, ay + i, white);
        if (D > 0)
        {
            x += dir;
            D = D + 2 * dx - 2 * dy;
        }
        else
        {
            D = D + 2 * dx;
        }
    }
}

void check(int ax, int ay, int bx, int by, TGAImage &image)
{
    if (std::abs(bx - ax) > std::abs(by - ay))
    {
        drawlineH(ax, ay, bx, by, image);
    }
    else
    {
        drawlineV(ax, ay, bx, by, image);
    }
}

void TriangleDraw(int ax, int ay, int bx, int by, int cx, int cy, TGAImage &image)
{
    /* The points(x and y) to be coloured will be in-between
    min_x and max_x and min_y and max_y */
    int min_x = std::min({ax, bx, cx});
    int max_x = std::max({ax, bx, cx});
    int min_y = std::min({ay, by, cy});
    int max_y = std::max({ay, by, cy});

    float length_bc = std::hypot(cx - bx, cy - by);
    float length_ca = std::hypot(ax - cx, ay - cy);
    float length_ab = std::hypot(bx - ax, by - ay);

    int max_aplha = static_cast<int>(length_bc * bc_thick);
    int max_beta = static_cast<int>(length_ca * ca_thick);
    int max_gamma = static_cast<int>(length_ab * ab_thick);

    /* Calculate signed-area of initial triangle.
       Times 2(x2) because we want to avoid floating point numbers.
       This will not effect our future calculations.
       Formula used for area calc: Surveyor's formula
    */
    int tri_intitial_x2 = CalcArea(ax, ay, bx, by, cx, cy);
    if (tri_intitial_x2 == 0)
    {
        return;
    }

    /*As the area of tirangle can be negative, this piece of code
    ensures that the area will always be positive
    */
    if (tri_intitial_x2 < 0)
    {
        std::swap(bx, cx);
        std::swap(by, cy);
        tri_intitial_x2 = -tri_intitial_x2; // Now guaranteed positive
    }

    for (int x = min_x; x <= max_x; x++)
    {
        for (int y = min_y; y <= max_y; y++)
        {
            /*Signed area depends strictly on vertex order.
            For triangle A -> B -> C, the three sub-triangles
            must maintain the same cyclic winding:
            */

            /*B->C->P
              C->A->P
              A->B->P
            */

            int alpha_x2 = CalcArea(bx, by, cx, cy, x, y);
            int beta_x2 = CalcArea(cx, cy, ax, ay, x, y);
            int gamma_x2 = CalcArea(ax, ay, bx, by, x, y);

            if (tri_intitial_x2 > 0)
            {
                if (alpha_x2 >= 0 && beta_x2 >= 0 && gamma_x2 >= 0)
                {
                    /*Explanation will be present in README.md*/
                    if (alpha_x2 <= max_aplha || beta_x2 <= max_beta || gamma_x2 <= max_gamma)
                    {
                        image.set(x, y, white);
                    }
                }
            }

            else
            {
                if (alpha_x2 <= 0 && beta_x2 <= 0 && gamma_x2 <= 0)
                {
                    image.set(x, y, white);
                }
            }
        }
    }
}

int main()
{
    int width = 1024;
    int height = 1024;
    int ax, ay, bx, by, cx, cy;

    TGAImage framebuffer = {width, height, TGAImage::RGB};

    ax = 100;
    bx = 312;
    cx = 567;
    ay = 100;
    by = 729;
    cy = 300;

    framebuffer.set(ax, ay, white);
    framebuffer.set(bx, by, white);
    framebuffer.set(cx, cy, white);

    check(ax, ay, bx, by, framebuffer);
    check(bx, by, cx, cy, framebuffer);
    check(cx, cy, ax, ay, framebuffer);

    TriangleDraw(ax, ay, bx, by, cx, cy, framebuffer);

    framebuffer.write_tga_file("WiredTri.tga");
}