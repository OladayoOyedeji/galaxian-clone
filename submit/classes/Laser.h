#ifndef LASER_H
#define LASER_H

#include "Entity.h"


class Laser: public Entity
{
public:
    Laser(const Entity & entity)
        : Entity(entity.get_x() + entity.get_w() / 2, entity.get_y())
    {
        is_ship = entity.is_ship;
        if (entity.is_ship)
        {
            set_rect(2, 15, 0, 0, 255);
            dy = -10;
            dx = 0;
        }
        else
        {
            set_rect(2, 10, 255, 0, 0);
            dy = 10;
            dx = 0;
        }
        
    }
    
private:
};


#endif
