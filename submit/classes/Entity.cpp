#include "Entity.h"

Image * Entity::images[5] = {
    //new Image("images/galaxian/GalaxianGalaxip.gif"),
    new Image("images/galaxian/Blue_Galaxian.png"),
    new Image("images/galaxian/GalaxianFlagship.gif"),
    new Image("images/galaxian/GalaxianRedAlien.gif"),
    new Image("images/galaxian/GalaxianPurpleAlien.gif"),
    new Image("images/galaxian/GalaxianAquaAlien.gif")
};

void Entity::draw(Surface & surface)
{
    if (alive)
    {
        if (is_image)
        {
            surface.put_image(*image, rect);
        }
        else
        {
            surface.put_rect(rect.x, rect.y, rect.w, rect.h, r, b, g);
        }
    }
}

void Entity::move()
{
    if (alive)
    {
        rect.x += dx;
        rect.y += dy;
        
    }
}
