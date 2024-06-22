#ifndef AQUAALIEN_H
#define AQUAALIEN_H

class AquaAlien: public Enemy
{
  public:
    AquaAlien(int x, int y)
        : Enemy(4, 100)
    {
        set_x(x);
        set_y(y);
        x_ = x;
        y_ = y;
    }
  private:
};

#endif
