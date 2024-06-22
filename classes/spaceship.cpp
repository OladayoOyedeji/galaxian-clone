#include "spaceship.h"

Image * spaceship::images[2] = {
    new Image("images/galaxian/GalaxianGalaxip.gif"),
    new Image("images/galaxian/GalaxianPurpleAlien.gif")
};

Vector * spaceship::vectors[2] = {
    new Vector(W/2, H),
    new Vector(W/2, 0),
};

void spaceship::print(Surface & surface)
{
    if (alive)
    {
        surface.put_image(*image, rect);
        
        for (int i = 0; i < laser_length;  ++i) 
        {
            //(laser + i)->print(surface);
        }
    }
}

void spaceship::move(int dx, int dy)
{
    rect.x += dx;
    rect.y += dy;
}

// void spaceship::shoot()
// {
//     // if (laser_length < 100)
//     // {
//     //     laser[laser_length]= Laser(rect.x + rect.w / 2, rect.y, 3, 20, 45, 255, 12);
//     //     laser_length++;
//     // }
    
    
// }
