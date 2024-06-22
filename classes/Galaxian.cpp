#include "Galaxian.h"

void Galaxian::get_input(KeyPressed & keypressed)
{
    if (alive)
    {
        if (keypressed[LEFTARROW])
        {
            move_left();
        }
        else if (keypressed[RIGHTARROW])
        {
            move_right();
        }
        if (get_x() < 0)
        {
            set_x(0);
        }
        if (get_x() + h > W)
        {
            set_x(W - h);
        }
    }
    
    
    
}
