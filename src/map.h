#include "raylib.h"
#include <vector> 
#include "enumaration.h"
#include "data.h"
#include <cmath>
#include <iostream>
#define MAP_MAX_SIZE 50
class Map{
    public:
        Map(int x, int y);
        //void loadMap();
        void drawMap();
        //void clearMap();
        //void setMap(int x, int y);
        //char getMap(int x, int y);
        //void setMapSize(int x, int y);
        //int getMapSizeX();
        //int getMapSizeY();
    private:
        int mapSizeX;
        int mapSizeY;
        int mapMaxSizeX = MAP_MAX_SIZE;
        int mapMaxSizeY = MAP_MAX_SIZE;
        int leftOffest;
        int topOffest;
        GridElement grid[MAP_MAX_SIZE][MAP_MAX_SIZE];
        int tileSize = 20;
        std::vector<Color> tilesColors;
};
