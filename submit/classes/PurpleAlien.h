#ifndef PURPLEALIEN_H
#define PURPLEALIEN_H

class PurpleAlien: public Enemy
{
  public:
    PurpleAlien(int x, int y)
        : Enemy(3, 200)
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
            if (periodic)
            {
                if (MOVE_LEFT)
                    move_left();
                else
                    move_right();
            }
            else if (jumping)
            {
                if (g.alive && get_y() < g.get_y())
                {
                    homing(g);
                }
                else
                {
                    move_down();
                    move_left();
                }
                
                // dy = 1;
            //     if (g.alive)
            //     {
            //         if (get_x() > g.get_x())
            //         {
            //             dx = -5;
            //         }
            //         else
            //             dx = 5;
            
            //         move();
            //         int of = get_x() - g.get_x();
            //         if (of < 0)
            //         {
            //             of *= -1;
            //         }
            //         if (of < 20)
            //         {
            //             jumping = false;
            //             diving = true;
            //         }
            //     }
            //     else
            //     {
            //         dx = 0; move();
            //         if (get_y() > H + get_h())
            //         {
            //             returning = true;
            //         }
            //     }
            // }
            // else if (diving)
            // {
                
            //     dy = 2;
            //     if (g.alive && !continuing)
            //     {
                    
            //         set_x(g.get_x());
            //         //dx = 100 * sin(3.141 * get_y());
            //         //dx = 50 * sin(3.141 * (get_y()));
            //         dx = 50 * sin(3 * (get_y() - H));
            //         continuing = false;
            //     }
            //     else
            //     {
            //         dx = 8 * sin(3.141 * get_y() / 100);
            //         continuing = true;
            //     }
            //     move();
                if (get_y() >= H)
                {
                    set_y(0 - 2 * get_h() - 3);
                    jumping = false;
                    returning = true;
                    periodic = false;
                }
                
            }
            
            else if (returning)
            {
                dy = 2;
                set_x(8 * sin(3 * get_y() / 100)+ (x_ + offset));
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
    
private:
};

#endif
        
