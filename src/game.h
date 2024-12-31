#include <iostream>
#include <vector>   
#include <ctime>
#include <utility>
#include "door.h"
#include <algorithm>
#include <random>
#include <map>
#include "Map.h"
#include "Player.h"
#include "enumaration.h"
class Game{
public:
    Game(/* args */);
    void display();
    void handleInput();
    void movePlayer(Direction dir);
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
    bool linkMaps();
    bool teleport(int x, int y);
    bool breakWall();
    
    //std::vector<std::pair<int, std::pair<int, int>>> doors;
    std::pair<int,Door> escapedDoor;
    std::vector<std::pair<int,Door>> doorsList;
    float speed = 3;
    float initialTime;
    Player player;
};


