#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "Entity.h"
#include "Surface.h"

class Explosion
{
public:
    Explosion(const Entity & entity)
        : r(0), r2(0), finished(false),
          r_(195), g_(120), b_(0),
          x(entity.get_x() + entity.get_w() / 2),
          y(entity.get_y() + entity.get_h() / 2),
          final_r(entity.get_w() / 2)
    {}
    void explode(Surface & surface);
    
    bool finished;
    int x, y;
    int r, r2;
    int final_r;
    int r_, g_, b_;
};

#endif
