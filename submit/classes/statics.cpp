#include "statics.h"

int statics::size = 48;

int statics::FLAG_S = 2;
int statics::RED_A = 6;
int statics::PUR_A = 10;
int statics::AQUA_A = 30;
const int statics::MAX_LIVES = 3;

Sound * statics::sounds[2] = {new Sound("sounds/laser.wav"),
                              new Sound("sounds/explosion.wav")};

int statics::MAX_X;
int statics::MIN_X;
int statics::offset_x = 0;
int statics::score = 0;

bool statics::e_shoot = false;
bool statics::enter_pressed = false;

int statics::sec = 0;
int statics::msec = 0;
