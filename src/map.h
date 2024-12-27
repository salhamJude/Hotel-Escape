#ifndef MAP_H
#define MAP_H


#include <vector> 
#include "enumaration.h"
#include "data.h"
#include <cmath>
#include <iostream>
#include <queue>
#include <utility>
//#include "door.h"

#define MAP_MAX_SIZE 50

class Map{
    public:
        Map(int x, int y);
        Map();
        //void loadMap();
        void drawMap();
        void generateMapElements();
        void setPlayerPosition(std::pair<int, int>& playerPosition);
        void movePlayer(Direction dir, std::pair<int, int>& playerPosition);
        void removeDoor(int x, int y);
        std::vector<std::pair<int, int>> getDoors();
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
};

#endif //MAP_H