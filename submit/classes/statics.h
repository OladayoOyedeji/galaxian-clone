#ifndef STATICS_H
#define STATICS_H

#include "Sound.h"

class statics
{
  public:
    
    static int size;
    
    static int FLAG_S;
    static int RED_A;
    static int PUR_A;
    static int AQUA_A;
    static const int MAX_LIVES;
    
    
    static int MAX_X;
    static int MIN_X;
    static int offset_x;
    static int score;
    
    static bool e_shoot;
    static bool enter_pressed;
    
    static int sec;
    static int msec;
    static Sound * sounds[2];

    
    static void deallocate()
    {
        if (sounds[0] != nullptr)
        {
            delete sounds[0];
            sounds[0] = nullptr;
        }
        if (sounds[1] != nullptr)
        {
            delete sounds[1];
            sounds[1] = nullptr;
        }
    }

};


#endif
