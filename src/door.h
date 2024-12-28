#ifndef DOOR_H
#define DOOR_H

#include "map.h"

class Door{
    public:
        Door();
        Door(int x, int y, int  from);
        Door(int x, int y, int dx, int dy, int  from, int  to);
        void setDestination(int x, int y);
        void setOrigin(int x, int y);
        void setFrom(int  from);
        void setTo(int  to);
        bool isCorrecpondingDoor(int x, int y, int fr); 
        bool hasDestination();  
        int getFrom();
        int getTo();
        int getDestinationX();
        int getDestinationY();
        int getOriginX();
        int getOriginY();
    private:
        int ox;
        int oy;
        int dx;
        int dy;
        int from;
        int to;
};

#endif //DOOR_H