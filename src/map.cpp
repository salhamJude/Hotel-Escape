#include "map.h"

Map::Map(int x, int y)
{
    if(x > mapMaxSizeX || y > mapMaxSizeY)
    {
        x = mapMaxSizeX;
        y = mapMaxSizeY;
    }

    mapSizeX = x;
    mapSizeY = y;

    leftOffest = 0;
    topOffest = 0;

    for (int i = 0; i < mapMaxSizeX; i++)
    {
       for (int j = 0; j < mapMaxSizeY; j++)
       {
              grid[i][j] = GridElement::EMPTY;
       }
       
    }

    if(mapSizeX < mapMaxSizeX){
        leftOffest = round((mapMaxSizeX - mapSizeX) / 2);
    }

    if(mapSizeY < mapMaxSizeY){
        topOffest = round((mapMaxSizeY - mapSizeY) / 2);
    }

    std::cout << "leftOffest: " << leftOffest << std::endl;
    std::cout << "topOffest: " << topOffest << std::endl;
    for (int i = 0; i < mapMaxSizeX; i++)
    {
       for (int j = 0; j < mapMaxSizeY; j++)
       {
            if((i>= leftOffest && i < mapSizeX + leftOffest) && (j >= topOffest && j < mapSizeY + topOffest)){
                grid[i][j] = GridElement::PATH;
                std::cout << "*" ;
            }else{
                std::cout << "0";
            }
       }
       std::cout << std::endl;
    }
    tilesColors = Data::tilesColors();
}

void Map::drawMap()
{  
    Color clr;

    for (int row = 0; row < mapMaxSizeX; row++)
    {
       for (int column = 0; column < mapMaxSizeY; column++)
       {
            switch (grid[row][column])
            {
            case GridElement::EMPTY:
                clr = tilesColors[0];
                break;
            case GridElement::WALL:
                clr = tilesColors[5];
                break;
            case GridElement::PLAYER:
                clr = tilesColors[2];
                break;
            case GridElement::DOOR:
                clr = tilesColors[3];
                break;
            case GridElement::PATH:
                clr = tilesColors[1];
                break;
            default:
                break;
            }

            DrawRectangle(column * tileSize+1, row * tileSize+1, tileSize-1, tileSize-1, clr);
       }
       
    }
}
