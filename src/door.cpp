#include "door.h"


Door::Door(int x, int y, const Map &from, const Map &to)
{
    this->x = x;
    this->y = y;
    this->from = from;
    this->to = to;
}
