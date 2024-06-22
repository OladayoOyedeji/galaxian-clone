#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "Laser.h"
#include "Constants.h"
#include "Event.h"
#include "Image.h"
#include "compgeom.h"
#include "Includes.h"

class Vector
{
public:
    Vector(int x = 0, int y = 0)
        : x_(x), y_(y)
    {}
    int get_x() const
    {
        return x_;
    }
    int get_y() const
    {
        return y_;
    }
private:
    int x_, y_;
};

class spaceship
{
public:
    
    spaceship(int i)
        : image(images[i]), rect(image->getRect()), laser_length(0), alive(true)
    {
        rect.y = (vectors[i]->get_y());
        rect.x = vectors[i]->get_x();
        if (rect.y >= H)
        {
            rect.y -= rect.h;
        }
    }
    
    ~spaceship()
    {
    }
    void move(int dx = 0, int dy = 0);
    void print(Surface & surface);
    //void shoot();
private:
    Image * image;
    //Laser laser[100];
    int laser_length;
    static Image * images[2];
    static Vector * vectors[2];
    int x, y, w, h;
    bool alive;
public:
    Rect rect;
};

#endif
