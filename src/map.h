#ifndef MAP_H
#define MAP_H


#include <vector> 
#include "enumaration.h"
#include "data.h"
#include <cmath>
#include <iostream>
#include <queue>
#include <utility>
#include "Player.h"
//#include "door.h"
#include <functional>

#define MAP_MAX_SIZE 50

class Map{
    public:
        Map(int x, int y);
        Map();
        ~Map();
        Map& operator=(const Map& other);
        //void loadMap();
        void drawMap();
        void drawMap2(Player& player);
        void generateMapElements();
        void setPlayerPosition(std::pair<int, int>& playerPosition, Player& Player);
        void movePlayer(Direction dir, Player& player, std::function<bool(int,int)> teleportCallBack, int speed);
        void removeDoor(int x, int y);
        std::vector<std::pair<int, int>> getDoors();
        bool openDoor(int x, int y, Player& player);
        bool breakWall(Player& player, Direction dir, int speed);
    private:
        void generateWalls();
        void generateWall(int posX, int posY, Direction dir, int length, int mapSizeX, int mapSizeY);
        void generateCountourWalls();
        //void generateEscapeDoor();
        void generateDoors();
        void floodFill(int x, int y, std::vector<std::pair<int, int>>& enclosedArea);
        bool isEnclosed(const std::vector<std::pair<int, int>>& enclosedArea);
        void placeDoor(const std::vector<std::pair<int, int>>& enclosedArea);
        void detectAndFixEnclosedSpaces();
        void move(int x, int y, Player& player, int speed);
        void teleport(int x, int y, Player& player, std::function<bool(int,int)> teleportCallBack);
        std::vector<std::pair<Texture2D, Rectangle>> getTilesTextures();
        int mapSizeX;
        int mapSizeY;
        int mapMaxSizeX = MAP_MAX_SIZE;
        int mapMaxSizeY = MAP_MAX_SIZE;
        int leftOffest;
        int topOffest;
        GridElement grid[MAP_MAX_SIZE][MAP_MAX_SIZE];
        int tileSize = 20;
        std::vector<Color> tilesColors;
        std::vector<std::pair<int, int>> doors;
        std::vector<std::pair<Texture2D, Rectangle>> tilesTextures;
        int snapToGrid(int position);
        int desnity = 120;
        int variation = 40;
        int fluctuation  = 100;
        Texture2D tileTexture;
};

#endif //MAP_H