#ifndef FLAGSHIP_H
#define FLAGSHIP_H

#include "Enemy.h"

class Flagship: public Enemy
{
  public:
    Flagship(int x, int y)
        : Enemy(1, 400)
    {
        x_ = x;
        y_ = y;
        set_x(x);
        set_y(y);
    }
    
  private:
};

#endif
