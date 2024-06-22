#ifndef GAME_H
#define GAME_H

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
#include "statics.h"

enum Gamestate
{
    PLAY,
    INSTRUCTION,
    EXIT,
    
};

void set_formation(std::vector< Enemy * > & enemy, int size);
void shoot(std::vector< Laser * > & , const Entity &);
void get_input(std::vector< Laser * > &, KeyPressed &, Galaxian &, bool &);
void move_stars();
void draw_Galaxian();
void draw_stars(Star star[], int star_size, Surface & surface);
void draw_enemy(const std::vector< Enemy * > & enemy, Surface & surface);
void draw_lasers(std::vector< Laser * > & laser, Surface & surface);
void draw_explosion(std::vector< Explosion *> &  e, Surface & surface);
void draw_lives(int lives, Surface & surface);
void draw_text(Surface & surface, const char[],
                Font & font, Color & color,
               int x, int y);
void draw_all(Galaxian ship[], int lives,
              std::vector< Enemy * > & enemy,
              std::vector< Laser * > & laser,
              std::vector< Explosion *> & e,
              Surface & surface);
void die_enemy(Galaxian & ship,
               std::vector< Enemy * > & enemy,
               std::vector< Laser * > & laser,
               std::vector< Explosion * > & e);
void run_enemy(std::vector< Laser * > & laser,
               std::vector< Enemy * > & enemy,
               const Galaxian & ship);
void update_all(Galaxian ship[], int & lives,
                std::vector< Enemy * > & enemy,
                std::vector< Laser * > & laser,
                std::vector< Explosion *> & e,
                Surface & surface,
                KeyPressed & keypressed,
                bool & s_pressed);
void add_explosion(std::vector< Explosion * > & e, Entity * entity);
void enemy_shoot(std::vector< Laser * > & laser, Enemy & enemy);
void draw_welcome(Surface & surface, int option);
void draw_title(Surface & surface);
void draw_name(Surface & surface);
void draw_game_over(Surface & surface);
void draw_scores(Surface & surface);
void draw_new_wave(Surface & surface);
bool enemies_dead(std::vector< Enemy * > & enemy);
void clear_enemy(std::vector< Enemy * > & enemy);
void clear_lasers(std::vector< Laser * > & laser);
void clear_explosions(std::vector< Explosion * > & e);
void clear_all(std::vector< Enemy * > & enemy,
               std::vector< Laser * > & laser,
               std::vector< Explosion * > & e);
void reset_enemy(std::vector< Enemy * > & enemy);
void reset_lasers(std::vector< Laser * > & laser);
void reset_explosion(std::vector< Explosion * > & e);
void reset(std::vector< Enemy * > & enemy,
           std::vector< Laser * > & laser,
           std::vector< Explosion * > & e,
           Galaxian ship[]);
int size_i(int i);
void int_to_char(int int_, char string_[]);
void draw_score(Surface & surface, char []);
void MAX_MIN_computation(std::vector <Enemy *> & enemy);
void gameplay();

#endif
