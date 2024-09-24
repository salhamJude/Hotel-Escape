#ifndef MAP_H
#define MAP_H


#include "raylib.h"
#include <vector> 
#include "enumaration.h"
#include "data.h"
#include <cmath>
#include <iostream>
//#include "door.h"

#define MAP_MAX_SIZE 50

class Map{
    public:
        Map(int x, int y);
        Map();
        //void loadMap();
        void drawMap();
        //void clearMap();
        //void setMap(int x, int y);
        //char getMap(int x, int y);
        //void setMapSize(int x, int y);
        //int getMapSizeX();
        //int getMapSizeY();
        void generateMapElements();
    private:
        void generateWalls();
        //void generateDoors();
        void generateWall(int posX, int posY, Direction dir, int length, int mapSizeX, int mapSizeY);
        void generateCountourWalls();
        //void generateEscapeDoor();
        void generateDoors();
        void floodFill(int x, int y, std::vector<std::pair<int, int>>& spaceLocations, std::vector<std::vector<bool>>& visited); 
        void placeDoorAroundSpace(const std::vector<std::pair<int, int>>& spaceLocations);
        bool isInBounds(int x, int y);
        int mapSizeX;
        int mapSizeY;
        int mapMaxSizeX = MAP_MAX_SIZE;
        int mapMaxSizeY = MAP_MAX_SIZE;
        int leftOffest;
        int topOffest;
        GridElement grid[MAP_MAX_SIZE][MAP_MAX_SIZE];
        int tileSize = 20;
        std::vector<Color> tilesColors;
        //std::vector<Door> doors;
};

#endif //MAP_H