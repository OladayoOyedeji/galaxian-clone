#ifndef ENTITY_H
#define ENTITY_H

#include "Constants.h"
//#include "Event.h"
#include "Surface.h"
#include "Image.h"
#include "Includes.h"

const int SHIP = 0,
    FLAG_ALIEN = 1,
    RED_ALIEN = 2,
    PURP_ALIEN = 3,
    AQUA_ALIEN = 4;

const int SIZE_I = 5;

class Entity
{
  public:
    Entity()
        : image(nullptr), alive(false), is_image(false), is_ship(false)
    {}
    Entity(int x_, int y_)
        : image(nullptr), alive(true), is_image(false)
    {
        rect.x = x_;
        rect.y = y_;
    }
    Entity(const int i)
        : image(images[i]), rect(image->getRect()), alive(true), is_image(true),
          is_ship(false)
    {
        if (i == 0)
        {
            is_ship = true;
        }
        w = rect.w;
        h = rect.h;
    }
    ~Entity()
    {}

    Entity operator=(const Entity & E)
    {
        image = E.image;
        rect = E.rect;
        alive = E.alive;
        is_image = E.is_image;
        return *this;
    }
    
    void set_x(int x_)
    {
        rect.x = x_;
    }
    int get_x() const
    {
        return rect.x;
    }
    int get_y() const
    {
        return rect.y;
    }
    int get_h() const
    {
        return rect.h;
    }
    int get_w() const
    {
        return rect.w;
    }
    void set_y(int y_)
    {
        rect.y = y_;
    }
    void set_rect(int w_, int h_, int r_, int g_, int b_)
    {
        rect.w = w_;
        rect.h = h_;
        r = r_;
        g = g_;
        b = b_;
    }
    void set_live(bool state)
    {
        alive = state;
    }
    virtual void draw(Surface & surface);
    virtual void move();
    void move_up()
    {
        rect.x -= 5;
    }
    void move_down()
    {
        rect.y += 5;
    }
    void move_left()
    {
        dx = -5;
        dy = 0;
        move();
    }
    void move_right()
    {
        dx = 5;
        dy = 0;
        move();
    }
    void kill()
    {
        set_live(false);
    }
    virtual void die(Entity & E)
    {
        if (alive && E.alive)
        {
            
            if ((rect.y < E.rect.y + E.rect.h && E.rect.y < rect.y + rect.h) && (rect.x < E.rect.x + E.rect.w && E.rect.x < rect.x + rect.w))
            {
                kill();
                E.kill();
                *this = Entity();
                
                collision = true;
            }
        }
    }
    bool is_collide(Entity & E)
    {
        if (alive && E.alive)
        return ((rect.y < E.rect.y + E.rect.h && E.rect.y < rect.y + rect.h) && (rect.x < E.rect.x + E.rect.w && E.rect.x < rect.x + rect.w));
        else
        {
            return false;
        }
    }

    bool collision = false;
    bool is_ship;
    bool alive;
    int w, h, dx, dy, r, g, b;
    static Image * images[SIZE_I];
  private:
    Image * image;
    Rect rect;
    bool is_image;
    //Explosion e;
    
    
};

#endif
