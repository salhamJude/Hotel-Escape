#include "door.h"

Door::Door()
{
}

Door::Door(int ox, int oy, int from)
{
    this->ox = ox;
    this->oy = oy;
    this->from = from;
    this->to = -1;
}

Door::Door(int ox, int oy, int dx, int dy, int from, int to)
{
    this->ox = ox;
    this->oy = oy;
    this->dx = dx;
    this->dy = dy;
    this->from = from;
    this->to = to;
}

void Door::setDestination(int x, int y)
{
    this->dx = x;
    this->dy = y;
}

void Door::setOrigin(int x, int y)
{
    this->ox = x;
    this->oy = y;
}

void Door::setFrom(int from)
{
    this->from = from;
}

void Door::setTo(int to)
{
    this->to = to;
}

bool Door::isCorrecpondingDoor(int x, int y, int fr)
{
    std::cout << "Checking if door is corresponding" << std::endl;
    std::cout << "x: " << x << " y: " << y << " from: " << fr << std::endl;
    std::cout << "dx: " << dx << " dy: " << dy << " from: " << from << std::endl;
    if (x == dx && y == dy && fr == this->from)
    {
        return true;
    }
    
    return false;
}

bool Door::hasDestination()
{
    if (to != -1)
    {
        return true;
    }
    return false;
}

int Door::getFrom()
{
    return from;
}

int Door::getTo()
{
    return to;
}

int Door::getDestinationX()
{
    return dx;
}

int Door::getDestinationY()
{
    return dy;
}

int Door::getOriginX()
{
    return ox;
}

int Door::getOriginY()
{
    return oy;
}
