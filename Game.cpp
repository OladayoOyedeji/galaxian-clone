#include "Game.h"
#include <ctime>


void set_formation(std::vector< Enemy * > & enemy, int size)
{
    int space = 3;
    
    
    Flagship f(0, 0);
    
    int distance = (W - (f.get_w() * 4) - ((statics::FLAG_S + 2) * space)) / 2;
    int height = 50;
    for (int i = 0; i < statics::FLAG_S; ++i)
    {
        enemy[i] = new Flagship(distance, height);
        distance += f.get_w() * 3 + space;
    }

    
    distance = (W - (enemy[0]->get_w() * statics::RED_A) - ((statics::RED_A - 2) * space)) / 2;
    height = enemy[0]->get_y() + enemy[0]->get_h() + space;
    
    for (int i = 0; i < statics::RED_A; ++i)
    {
        int j = 0;
        enemy[i + statics::FLAG_S] = new RedAlien(distance, height);
        distance += enemy[i]->get_w() + space;
        if (i >= statics::RED_A / 2)
        {
            j++;
        }
        (enemy[i + statics::FLAG_S])->set_daddy(enemy[j]); 
    }

      
    distance = (W - (enemy[0]->get_w() * statics::PUR_A) - ((statics::PUR_A - 2) * space)) / 2;
    height = enemy[statics::FLAG_S]->get_y() + enemy[0]->get_h() + space;
    for (int i = 0; i < statics::PUR_A; ++i)
    {
        enemy[i + statics::FLAG_S + statics::RED_A] = new PurpleAlien(distance, height);
        distance += enemy[i]->get_w() + space;
    }

    
    distance = (W - (enemy[0]->get_w() * statics::PUR_A) - ((statics::PUR_A - 2) * space)) / 2;
    height = enemy[statics::FLAG_S + statics::RED_A]->get_y() + enemy[0]->get_h() + space;
    for (int i = 0; i < statics::AQUA_A; ++i)
    {
        if (i % 10 == 0 && i != 0)
        {
            distance = (W - (enemy[0]->get_w() * statics::PUR_A) - ((statics::PUR_A - 2) * space)) / 2;
            height = enemy[statics::FLAG_S + statics::RED_A + statics::PUR_A + i - 1]->get_y() + enemy[0]->get_h() + space;
         
        }
        enemy[i + statics::FLAG_S + statics::RED_A + statics::PUR_A] = new AquaAlien(distance, height);
        distance += enemy[i]->get_w() + space;
    }

    Enemy::max = enemy[statics::FLAG_S + statics::RED_A];
    Enemy::min = enemy[size - 1];
    statics::MAX_X = enemy[statics::FLAG_S + statics::RED_A]->get_x();
    statics::MIN_X = enemy[size - 1]->get_x();
    statics::offset_x = 0;
    
}

void shoot(std::vector< Laser * > & laser, const Entity & E)
{
    int laser_length = int(laser.size()) + 1;
    laser.resize(laser_length);
    laser[laser_length - 1] = new Laser(E);
    
    statics::sounds[0]->play();
    
}

void get_input(std::vector< Laser * > & laser, KeyPressed & keypressed, Galaxian & ship, bool & s_pressed)
{
    ship.get_input(keypressed);
    if (ship.alive)
    {
        if (!s_pressed && keypressed[SPACE])
        {
            shoot(laser, ship);
            s_pressed = true;
        }
        if (!keypressed[SPACE])
        {
            s_pressed = false;
        }
    }
}

// void move_stars()
    
void draw_stars(Star star[], int star_size, Surface & surface)
{
    for (int i = 0; i < star_size; ++i)
    {
        star[i].print(surface);
    }
}
void draw_enemy(const std::vector< Enemy * > & enemy, Surface & surface)
{
    for (int i = 0; i < statics::size; ++i)
    {
        enemy[i]->draw(surface);
    }
}

void draw_lasers(std::vector< Laser * > & laser, Surface & surface)
{
    int laser_length = int(laser.size());
    for (int i = 0; i < laser_length; ++i)
    {
        laser[i]->draw(surface);
        laser[i]->move();
        if (laser[i]->alive)
        {
            if (laser[i]->get_y() <= 0 - laser[i]->get_h() || laser[i]->get_y() >= W)
            {
                laser[i]->kill();
            }
        }

    }
}

void draw_explosion(std::vector< Explosion *> & e, Surface & surface)
{
    int explosion_length = int(e.size());
    for (int i = 0; i < explosion_length; ++i)
    {
        e[i]->explode(surface);
    }
}

void draw_lives(int lives, Surface & surface)
{
    int distance = W - 30;
    Rect rect;
    rect.w = 15 / 2;
    rect.h = 15 / 2;
    rect.y = H - 30;
    for (int i = statics::MAX_LIVES - 1; i >= lives; --i)
    {
        rect.x = distance;
        surface.put_image(*(Entity::images[0]), rect);
        distance -= 40;
    }
    
}

// void draw_all();
void die_enemy(Galaxian & ship,
               std::vector< Enemy * > & enemy,
               std::vector< Laser * > & laser,
               std::vector< Explosion * > & e)
{
    int explosion_length = int(e.size());
    int laser_length = int(laser.size());
    for (int i = 0; i < laser_length; ++i)
    {
        for (int j = 0; j < statics::size; j++)
        {
            if (enemy[j]->is_collide(*(laser[i])) && (laser[i]->is_ship))
            {
                add_explosion(e, enemy[j]);
                statics::score += enemy[j]->points;
                enemy[j]->die(*(laser[i]));
            }
            
            if (ship.is_collide(*(enemy[j])))
            {
                add_explosion(e, enemy[j]);
                add_explosion(e, &ship);
                statics::score += enemy[j]->points;
                
                ship.die(*(enemy[j]));   
            }
            
            if (ship.is_collide(*(laser[i])) && !(laser[i]->is_ship))
            {
                 add_explosion(e, &ship);
                 ship.die(*(laser[i]));
            }  
            
           
        }
    }
}

void run_enemy(std::vector< Laser * > & laser, std::vector< Enemy * > & enemy, const Galaxian & ship)
{
    static bool MOVE_LEFT;
    if (statics::MAX_X <= 0)
    {
        MOVE_LEFT = false;
    }
    if (statics::MIN_X >= W - 32)
    {
        MOVE_LEFT = true;
    }
    if (MOVE_LEFT)
    {
        statics::MAX_X -= 5;
        statics::MIN_X -= 5;
        statics::offset_x -= 5;
    }
    else
    {
        statics::MAX_X += 5;
        statics::MIN_X += 5;
        statics::offset_x += 5;
    }
    // std::cout << statics::MAX_X << ' ' << statics::MIN_X << std::endl;
    for (int i = 0; i < statics::size; i++)
    {
        enemy[i]->run(ship, MOVE_LEFT, statics::offset_x);
        enemy_shoot(laser, *(enemy[i]));
    }
    
}

// void update_all();
void add_explosion(std::vector< Explosion * > & e, Entity * entity)
{
    int explosion_length = int(e.size()) + 1;
    e.resize(explosion_length);
    e[explosion_length - 1] = new Explosion(*entity);
        statics::sounds[1]->play();
    entity->collision = false;

}

void enemy_shoot(std::vector< Laser * > & laser, Enemy & enemy)
{
    if (enemy.alive)
    {
        int sedd = rand() % 5 + 120;
        if (enemy.get_y() > enemy.y_ + 20)
        {
            if (statics::msec % sedd == 0) 
                shoot(laser, enemy);
        }
    }
}

void update_all(Galaxian ship[], int & lives,
                std::vector< Enemy * > & enemy,
                std::vector< Laser * > & laser,
                std::vector< Explosion *> & e,
                Surface & surface,
                KeyPressed & keypressed,
                bool & s_pressed)
{
    
        if (statics::sec == 1 && ship[lives].alive)
        {
            //std::cout << sec << std::endl;
            srand((unsigned int) time(NULL));
            int rand_d = rand() % statics::size;
            int i = 0;
            while(!enemy[rand_d]->alive || !enemy[rand_d]->periodic)
            {
                rand_d = rand() % statics::size;
                if (i >= statics::size)
                    break;
                i++;
            }
            enemy[rand_d]->jumping = true;
            enemy[rand_d]->periodic = false;
                statics::sec = 0;
        }
        else if (!ship[lives].alive && statics::msec % 100 == 0)
        {
                lives++;
                statics::sec = 0;
            
        }

        if (lives < statics::MAX_LIVES)
        {
            get_input(laser, keypressed, ship[lives], s_pressed);
            run_enemy(laser, enemy, ship[lives]);
            die_enemy(ship[lives], enemy, laser, e);
        }
}

void draw_all(Galaxian ship[], int lives,
              std::vector< Enemy * > & enemy,
              std::vector< Laser * > & laser,
              std::vector< Explosion *> & e,
              Surface & surface)
{
    
    ship[lives].draw(surface);
    draw_enemy(enemy, surface);
    draw_lasers(laser, surface); 
    draw_explosion(e, surface);
    draw_lives(lives, surface);
}

void draw_title(Surface & surface)
{
    
    Font font("fonts/NormandyBeach-rgG6B.otf", 50);
    int r = 205;
    int g = 103;
    int b = 34;
    Color c = {Uint8(r), Uint8(g), Uint8(b)};
    Image image(font.render("GALXAXIAN", c));
    Rect rect = image.getRect();
    rect.x = (W / 2) - rect.w / 2;
    rect.y = (H / 2) - rect.h / 2;
    surface.put_image(image, rect);
    
}

void draw_name(Surface & surface)
{
    Font font("fonts/KawaguchiDemo-d9qz6.ttf", 20);
    int r = 0;
    int g = 0;
    int b = 255;
    Color c = {Uint8(r), Uint8(g), Uint8(b)};
    Image image(font.render("by Oladayo Robert Oyedeji", c));
    Rect rect = image.getRect();
    rect.x = (W / 2) - rect.w / 2;
    rect.y = H - rect.h;
    surface.put_image(image, rect);
}

void draw_welcome(Surface & surface, int option)
{
    draw_title(surface);
    draw_name(surface);
    Font font("fonts/options.ttf", 30);
    int r = 0;
    int g = 0;
    int b = 255;
    Color c = {Uint8(r), Uint8(g), Uint8(b)};
    Color c_ = {Uint8(r + 100), Uint8(g + 100), Uint8(b)};
    int x = 400;
    int y = 400;
    
    char fi[] = "PLAY";
    char fj[] = "INSTRUCTION";
    char fk[] = "EXIT";
    char * s[] = {fi, fj, fk};
    for (int i = 0; i < 3; ++i)
    {
        if (option == i)
        {
            draw_text(surface, ">", font, c_, x - 50, y - 5);
            draw_text(surface, s[i], font, c_, x - 5, y - 5);
        }
        else
        {
            draw_text(surface, s[i], font, c, x, y);
        }
        y += 30;
    }
    
}

void draw_text(Surface & surface, const char s[], Font & font, Color & color, int x, int y)
{
    Image image(font.render(s, color));
    Rect rect = image.getRect();
    rect.x = x;
    rect.y = y;
    surface.put_image(image, rect);
}

void draw_game_over(Surface & surface)
{
    Font font("fonts/RapidtechDemoItalic-51rdv.ttf", 50);
    int r = 0;
    int g = 0;
    int b = 255;
    Color c = {Uint8(r), Uint8(g), Uint8(b)};
    draw_text(surface, "GAME OVER BOZO", font, c, (W / 2) - 150, (H / 2) - 20);
}

bool enemies_dead(std::vector< Enemy * > & enemy)
{
    for (int i = 0; i < statics::size; ++i)
    {
        if (enemy[i]->alive)
        {
            return false;
        }
    }
    return true;
}

void clear_enemy(std::vector< Enemy * > & enemy)
{
    for (int i = 0; i < statics::size; ++i)
    {
        delete enemy[i];
    }
    enemy.resize(0);
    
}

void clear_lasers(std::vector< Laser * > & laser)
{
    int laser_length = int(laser.size());
    for (int i = 0; i < laser_length; ++i)
    {
        delete laser[i];
    }
    laser.resize(0);
}

void clear_explosions(std::vector< Explosion * > & e)
{
    int explosion_length = int(e.size());
    for (int i = 0; i < explosion_length; ++i)
    {
        delete e[i];
    }
    e.resize(0);
}

void clear_all(std::vector< Enemy * > & enemy,
               std::vector< Laser * > & laser,
               std::vector< Explosion * > & e)
{
    clear_enemy(enemy); clear_lasers(laser); clear_explosions(e);
}

void reset_enemy(std::vector< Enemy * > & enemy)
{
    clear_enemy(enemy);
    set_formation(enemy, statics::size);
}
    
void reset(std::vector< Enemy * > & enemy,
           std::vector< Laser * > & laser,
           std::vector< Explosion * > & e,
           Galaxian ship[])
{
    clear_all(enemy, laser, e);
    set_formation(enemy, statics::size);
    for (int i = 0; i < statics::MAX_LIVES; ++i)
    {
        ship[i] = Galaxian();
    }
}

void draw_new_wave(Surface & surface)
{
    Font font("fonts/Starjhol.ttf", 30);
    int r = 255;
    int g = 255;
    int b = 255;
    Color c = {Uint8(r), Uint8(g), Uint8(b)};
    // Image image(font.render("new wave incoming", c));
    // Rect rect = image.getRect();
    
    static int x = (W / 2) - 350 / 2;
    static int y = H;
    // surface.put_image(image, rect);
    draw_text(surface, "new wave incoming", font, c, x, y);
    y -= 5;
    
}

int size_i(int i)
{
    int s = 0;
    if (i == 0) return 1;
    // s++;
    while (i != 0)
    {
        i /= 10;
        s++;
    }
    return s;
 }


void int_to_char(int int_, char string_[])
{
    for (int i = 0; i < size_i(int_); ++i)
    {
        string_[i] = (int(int_ / pow(10, size_i(int_) - 1 - i)) % 10) + '0';
    }
    string_[size_i(int_)] = '\0';
}

void draw_score(Surface & surface, char score_c[])
{
    int x = 5, y = 5;
    int_to_char(statics::score, score_c);
    Font font("fonts/FightNight-w9V3.ttf", 20);
    Image image(font.render(score_c, WHITE));
    int r = 255;
    int g = 255;
    int b = 255;
    Color c = {Uint8(r), Uint8(g), Uint8(b)};
    draw_text(surface, "SCORE", font, c, x, y);
    Rect rect = image.getRect();
    rect.x = x; rect.y = y + 20;
    surface.put_image(image, rect);
}

void MAX_MIN_computation(std::vector <Enemy *> & aliens)
{
    if(Enemy::max != NULL && !(Enemy::max->alive))
    {
        Enemy::max = NULL;
       
        for(int i = 0; i < aliens.size(); ++i)
        {
            if(aliens[i]->alive)
            {
                if(Enemy::max == NULL)
                    Enemy::max = aliens[i];
                else if(aliens[i]->x_ < Enemy::max->x_)
                {
                    Enemy::max = aliens[i];
                    statics::MAX_X = Enemy::max->x_ + statics::offset_x;
                }
            }
        }
    }


    if(Enemy::min != NULL && !(Enemy::min->alive))
    {
        Enemy::min = NULL;
       
        for(int i = 0; i < aliens.size(); ++i)
        {
            if(aliens[i]->alive)
            {
                if(Enemy::min == NULL)
                    Enemy::min = aliens[i];
                else if(aliens[i]->x_ > Enemy::min->x_)
                {
                    Enemy::min = aliens[i];
                    statics::MIN_X = Enemy::min->x_ + statics::offset_x;
                }
            }
        }
    }
}

// void draw_instructions(Surface & surface)
// {
//     Font font("fonts/RapidtechDemoItalic-51rdv.ttf", 30);
//     draw_text(surface, "Hit the aliens", );
//     for (int i = 1; i < 5; ++i)
//     {
//         Rect rect = Entity::image[i]->get_rect();
//         rect.x = 
//     }
//     put_image()
// }
