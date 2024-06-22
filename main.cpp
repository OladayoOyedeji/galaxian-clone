#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <sstream>

#include "Includes.h"
#include "Constants.h"
#include "compgeom.h"
#include "Surface.h"
#include "Event.h"

#include "Star.h"
#include "Entity.h"
#include "Laser.h"
#include "spaceship.h"
#include "Enemy.h"
#include "Galaxian.h"
#include "Flagship.h"
#include "RedAlien.h"
#include "PurpleAlien.h"
#include "AquaAlien.h"
#include "Explosion.h"
#include "Game.h"



int main(int argc, char* argv[])
{
    Surface surface(W, H);
    Event event;
    
    
    // initialization of stars moving
    const int star_size = 100;
    Star star[star_size + 1];
    
    // initialization of ship
    Galaxian ship[statics::MAX_LIVES];
    
    // initialization of enemies
    std::vector< Enemy * >  enemy;
    enemy.resize(statics::size);
    set_formation(enemy, statics::size);
    
    // initialization of laser
    std::vector< Laser * > laser;
    int laser_length = 0;
    
    // initialization of explosion
    std::vector< Explosion * > e;
    int explosion_length = 0;
    
    // i mean you gotta know if space
    // is pressed so that you dont have
    // a giant beam of lasers but if you
    // want we can do that later
    bool s_pressed = false;

    // the rate at which the animation
    // runs which is 30 frames per second
    // i guess cause the sin curve was too
    // fast and the entire velocity was too
    // fast like how will my velocity be 1
    // and still fast i dont understand
    int RATE = 1000 / 30;

    // the render processes only strings so i
    // am writing this suicide note
    char score_c[1024];

    // gotta know how many lives bro has
    int lives = 0;

    // initilization of music during gameplay
    Music music("sounds/GameLoop.ogg");
    Music game("sounds/bye-bye-mewing_fMVssQz.ogg");
    

    int count = 0;

    Sound click("sounds/click.wav");
    bool welcome = true;
    //bool input_name = false;
    bool game_play = false;
    bool game_over = false;
    bool new_wave = false;
    
    //game.play();
    bool option[3] = {true, false, false};
    int cursor = 0;
    
    game.play();
    game.off();
    music.play();
    while (1)
    {
        if (event.poll() && event.type() == QUIT) break;
        int START = getTicks();
        KeyPressed keypressed = get_keypressed();

        // Welcome stage
        if (welcome)
        {
            bool keypress = true;
            static int count = 1;
            if (count == 5)
            {
                keypress = false;
                count = 0;
            }
            bool exit = false;
            if (keypressed[UPARROW] && !keypress)
            {
                if (cursor > 0)
                {
                    cursor--;
                    keypress = true;
                    click.play();
                }
                
            }
            if (keypressed[DOWNARROW]&& !keypress)
            {
                
                cursor++;
                cursor %= 3;
                keypress = true;
                click.play();
            }
            switch (cursor)
            {
                case PLAY:
                    if (keypressed[SDLK_RETURN])
                    {
                        welcome = false;
                        game_play = true;
                    }
                    break;
                case INSTRUCTION:
                    if (keypressed[SDLK_RETURN])
                    {
                        
                    }
                    break;
                case EXIT:
                    if (keypressed[SDLK_RETURN])
                    {
                        exit = true;
                        
                    }
                    break;
                    keypressed[SDLK_RETURN] = false;
                
            }
            if (exit)
            {
                break;
            }
            count++;
           
        }
        if (game_play)
        {
            // for my gameplay function
            update_all(ship, lives, enemy,
                       laser, e, surface,
                       keypressed, s_pressed);
            static int a = 0;
            MAX_MIN_computation(enemy);

            statics::msec++;
            if (statics::msec % 60 == 0)
            {
                statics::sec++;
            }
            
            if (lives > statics::MAX_LIVES - 1)
            {
                game_play = false;
                game_over = true;
                music.off();
                game.on();
                game.play();
                
                
            }
            else if (enemies_dead(enemy))
            {
                static int time = 0;
                if (time == 50)
                {
                    game_play = false;
                    new_wave = true;
                    statics::sec = 0;
                    time = 0;
                    
                }
                time++;
                
            }
        }
        else if (new_wave)
        {
            static int time = 0;
            
            if (time == 100)
            {
                clear_all(enemy, laser, e);
                set_formation(enemy, statics::size); 
                new_wave = false; 
                game_play = true;
                time = 0;
            }
            time++;
        }
        if (game_over)
        {
            if (keypressed[SDLK_RETURN])
            {
                welcome =  true;
                game_over = false;
                std::ofstream f("scores.txt", std::ios::app);
                f << statics::score << std::endl;
                statics::score = 0;
                lives = 0;
                reset(enemy, laser, e, ship);
                statics::enter_pressed = true;
                // set_formation(enemy, statics::size);
                keypressed[SDLK_RETURN] = false;
                game.off();
                music.on();
                music.play();
           
            }
            
        }

        // SCORE
        

        
        surface.lock();
        surface.fill(BLACK);

        draw_stars(star, star_size, surface);
        draw_score(surface, score_c);
        
        // for my gameplay function
        if (welcome)
        {
            draw_welcome(surface, cursor);
        }
        else if (game_play)
        {
            draw_all(ship, lives, enemy, laser, e, surface);
        }
        else if (new_wave)
        {
            draw_new_wave(surface);
        }
        else if (game_over)
        {
            draw_game_over(surface);
        }
        
        surface.unlock();
        surface.flip();
        
        int END = getTicks();
        int dt = RATE - END + START;
        if (dt > 0) delay(dt);
    }
 
    clear_all(enemy, laser, e);

    statics::deallocate();
    
    return 0;
}


