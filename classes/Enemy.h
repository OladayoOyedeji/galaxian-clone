#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "Laser.h"
#include "Galaxian.h"
#include <cmath>
#include <iostream>

#include "Entity.h"

class Enemy: public Entity
{
public:
    Enemy(const int i, int points_)
        : Entity(i), periodic(true), diving(false),
          returning(true), continuing(false),
          points(points_), daddy(NULL), r(2), ang(0),
          moveTimer(0)
    {
        set_x(0);
        set_y(0);
        dy = 0;
        dx = 5;
    }
    int limit;
    int limit_y;
    
    virtual void run(const Galaxian & ship, bool, int);
    void sin_div(const Galaxian &);

    void dive();
    void set_daddy(Enemy * daddy_)
    {
        daddy = daddy_;
    }

    void getCoords(const Galaxian & ship);
    void homing(const Galaxian & ship);
    
    Enemy * daddy;
    bool periodic;
    bool diving;
    bool returning;
    bool jumping;
    bool continuing;
    int x_, y_;
    int points;
    int moveTimer;
    int pOldX;
    int pOldY;
    static Enemy * max;
    static Enemy * min;
    
private:
    double r;
    double ang;
    const int a = 1;
};



#endif
