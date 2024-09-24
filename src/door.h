#ifndef DOOR_H
#define DOOR_H

#include "map.h"

class Door{
    public:
        Door(int x, int y, const Map& from, const Map& to);
        //void setX(int x);
        //void setY(int y);
        //int getX();
        //int getY();
        //void draw();
        //void erase();
    private:
        int x;
        int y;
        Map from;
        Map to;
};

#endif //DOOR_H