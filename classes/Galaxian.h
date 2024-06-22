#ifndef GALXAIAN_H
#define GALXAIAN_H


#include "spaceship.h"
#include "Entity.h"

class Galaxian: public Entity
{
public:
    Galaxian()
        : Entity(SHIP)
    {
        set_x(W / 2 - get_w() / 2);
        set_y(H - 2 * get_h());
        dy = 0;
        is_ship = true;
    }
    void get_input(KeyPressed & keypressed);
    
private:
    
};

#endif
