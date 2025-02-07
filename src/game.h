#ifndef GAME_H
#define GAME_H

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
#include "Button.h"

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
    void onGaming();
    ~Game();
private:
    bool linkMaps();
    bool teleport(int x, int y);
    bool breakWall();
    void drawInfo();
    void drawMenu();
    void drawPause();
    void newGame();
    void quitGame();
    void win();
    int getRemainingTime();
    
    std::vector<Map> maps;
    int currentMap;
    unsigned int numMaps;
    std::pair<int, int> playerPosition;
    //std::vector<std::pair<int, std::pair<int, int>>> doors;
    std::pair<int,Door> escapedDoor;
    std::vector<std::pair<int,Door>> doorsList;
    float speed = 3;
    float initialTime;
    float initialTime2;
    Player player;
    Font font;
    int chrono;
    int startTime;
    

    bool won = false;
    bool onGoing = false;
    bool pause = false;
    bool gameOver = false;
    int winMenuChrono = 5;
    Texture2D menu;
    Button *start;
    Button *quit;
};


#endif // GAME_H