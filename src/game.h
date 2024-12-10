#include <iostream>
#include "map.h"
#include <vector>   
#include <ctime>

class Game
{
private:
    std::vector<Map> maps;
    int currentMap;
    unsigned int numMaps;
    
public:
    Game(/* args */);
    void display();
    void handleInput();
    void movePlayer(Direction dir);
    void breakWall();
    int getNumMaps();
    int getCurrentMap();
    void nextMap();
    void previousMap();
    ~Game();
};


