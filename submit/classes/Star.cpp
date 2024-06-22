#include "Star.h"
#include "Surface.h"
#include "Constants.h"


void Star::print(Surface & surface)
{
    if (y > H + R)
    {
        *this = Star();
        y = 0;
    }
    y += dy;
    x += dx;
    surface.put_circle(x, y, R, r, g , b);
    
}
