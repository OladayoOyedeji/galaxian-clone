#ifndef STAR_H
#define STAR_H

#include "Surface.h"
#include "Constants.h"

class Star
{
public:
    Star()
        : x(rand() % W), y(rand() % H), R(rand() % 2 + 1), r(rand() % 256), g(rand() % 256), b(rand() % 256), dx(0), dy(1.5)
    {
        if (R == 1)
        {
            dy = 1;
        }
        else if (R == 2)
        {
            dy = 2;
        }
    }
    void print(Surface & surface);
private:
    int x;
    int y;
    int R;
    int r;
    int g;
    int b;
    int dx;
    int dy;
};

#endif
