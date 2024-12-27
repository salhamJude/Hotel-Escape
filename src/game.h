#include <iostream>
#include "raylib.h"
#include <vector>   
#include <ctime>
#include <utility>
#include "door.h"
#include <algorithm>
#include <random>
#include <map>
#include "Map.h"

class Game{
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
private:
    std::vector<Map> maps;
    int currentMap;
    unsigned int numMaps;
    std::pair<int, int> playerPosition;
    void linkMaps();
    
    //std::vector<std::pair<int, std::pair<int, int>>> doors;
    std::pair<int,Door> escapedDoor;
    std::vector<std::pair<int,Door>> doorsList;
};


