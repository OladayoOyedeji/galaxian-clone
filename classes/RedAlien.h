#ifndef REDALIEN_H
#define REDALIEN_H

#include "Flagship.h"
#include "Enemy.h"

class RedAlien: public Enemy
{
  public:
    RedAlien(int x, int y)
        : Enemy(2, 300)
    {
        set_x(x);
        set_y(y);
        x_ = x;
        y_ = y;
    }
    
    virtual void run(const Galaxian & g, bool MOVE_LEFT, int offset)
    {
        if (alive)
        {
        if (daddy->alive)
        {
            set_x(daddy->get_x() - (daddy->x_ - x_));
            set_y(daddy->get_y() - (daddy->y_ - y_));
            if (get_y() != y_)
            {
                periodic = false;
                jumping = true;
            }
            else
            { 
                periodic = true;
                jumping = false;
            }
        }
        else
        {
            if (periodic)
            {
                if (MOVE_LEFT)
                    move_left();
                else
                    move_right();
            }
            else if (jumping)
            {
                dy = 1;
                    dy = 2;
                    dx = 8 * sin(3.141 * get_y() / 100);
                    continuing = true;
                    move();
                    if (get_y() >= H)
                    {
                        set_y(0 - 2 * get_h() - 3);
                        diving = false;
                        returning = true;
                        periodic = false;
                        jumping = false;
                    }
                
            }
            else if (diving)
            {
                //dy = 32;
                dy = 2;
                if (g.alive && !continuing)
                {
                    set_x(8 * sin(3.141 * get_y() / 100)+ g.get_x());
                    continuing = false;
                }
                else
                {
                    set_x(8 * sin(3.141 * get_y() / 100) + get_x());
                    continuing = true;
                }
                set_y(get_y() + dy);
                //std::cout << get_x() << std::endl;
                //dy /= 3;
                if (get_y() >= H)
                {
                    set_y(0 - 2 * get_h() - 3);
                    diving = false;
                    returning = true;
                    periodic = false;
                }
                
                
                
            }
            else if (returning)
            {
                dy = 2;
                set_x(50 * sin(3 * (get_y() - H))+ (x_ + offset));
                //std::cout << x_ << ' ' << y_ << '\n';
                set_y(get_y() + dy);
                if (get_y() > y_)
                {
                    set_x(x_ + offset);
                    set_y(y_);
                    returning = false;
                    periodic = true;
                }
            }
        }
        }
    }
    
private:
};

#endif
