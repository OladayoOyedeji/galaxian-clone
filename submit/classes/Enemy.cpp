#include "Enemy.h"

Enemy * Enemy::max = NULL;
Enemy * Enemy::min = NULL;

void Enemy::run(const Galaxian & g, bool MOVE_LEFT, int offset)
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
            // dx = 1;
            // set_x(get_x() + dx);
            // set_y(4 * (get_y() + 1) - (pow((dx - get_x() + 2), 2)) / 4);
            // if (get_y() < y_)
            // {
            //     jumping = false;
            //     diving = true;
            // }
            // dy = 1;
            // if (g.alive)
            // {
            //     if (get_x() > g.get_x())
            //     {
            //         dx = -5;
            //     }
            //     else
            //         dx = 5;
            
            // move();
            // int of = get_x() - g.get_x();
            // if (of < 0)
            // {
            //     of *= -1;
            // }
            // if (of < 20)
            // {
            //     jumping = false;
            //     diving = true;
            // }
            // }
            // else
            // {
            //     dx = 0; move();
            //     if (get_y() > H + get_h())
            //     {
            //         returning = true;
            //     }
            // }
            ang += 0.1;
            r = double(a) * (ang);
            set_x(r * cos(ang) + get_x());
            set_y(-(r * sin(ang)) + get_y());
            if (get_y() > y_)
            {
                jumping = false;
                diving = true;
            }
            
        }
        else if (diving)
        {
            //dy = 32;
            // dy = 2;
            // if (g.alive && !continuing)
            // {
                
            //     set_x(g.get_x());
            //     //dx = 100 * sin(3.141 * get_y());
            //     //dx = 50 * sin(3.141 * (get_y()));
            //     dx = 50 * sin(3 * (get_y() - H));
            //     continuing = false;
            // }
            // else
            // {
            //    dx = 8 * sin(3.141 * get_y() / 100);
            //     continuing = true;
            // }
            // move();
            // //std::cout << get_x() << std::endl;
            // //dy /= 3;
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
            }
            
        }
        else if (returning)
        {
            dy = 2;
            set_x(30 * sin(3 * get_y()) + (x_ + offset));
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

void Enemy::sin_div(const Galaxian & ship)
{
    dy = 2;
    set_x(150 * sin(3 * (get_y() - H))+ ship.get_x());
    set_y(get_y() + dy);
    //std::cout << get_x() << std::endl;
    //dy /= 3;
    if (get_y() >= H)
    {
        set_y(0);
    }
}

void Enemy::getCoords(const Galaxian & ship)
{
    pOldX = ship.get_x(), pOldY = ship.get_y();
}

void Enemy::homing(const Galaxian & ship)
{
    //delay acquisition of target, dont stop moving towards last coordinates
    if (moveTimer >= 10) {moveTimer = 0; getCoords(ship);}
    if (pOldY > get_y())
    {move_down();}
    if (pOldX > get_x())
    {move_right();}
    if (pOldX < get_x())
    {move_left();}
    ++moveTimer;
}
