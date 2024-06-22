#include "Explosion.h"

void Explosion::explode(Surface & surface)
{

    if (!finished)
    {
        if (r < final_r)
        {
            r += 2;
        }
        else if (r2 < final_r)
        {
            r2 += 2;
        }
        //std::cout << r2 << std::endl;
        if (r2 >= final_r)
        {
            finished = true;
        }
        //surface.lock();
        //surface.fill(BLACK);
        surface.put_circle(x, y, r, r_, g_, b_);
        surface.put_circle(x, y, r2, 0, 0, 0);
        //surface.unlock();
        //surface.flip();
        //delay(5);
    }
}
