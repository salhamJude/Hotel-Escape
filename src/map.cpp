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
            }
       }
    }
    tilesColors = Data::tilesColors();
    generateMapElements();
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
            if(grid[row][column] == GridElement::EMPTY){
                DrawRectangle(column * tileSize, row * tileSize, tileSize, tileSize, clr);
            }else{
                DrawRectangle(column * tileSize+1, row * tileSize+1, tileSize-1, tileSize-1, clr);
            }
       }
       
    }

}

void Map::generateMapElements()
{
    this->generateWalls();
}

void Map::generateWalls()
{
    int nbrWall = (mapSizeY / 3) + rand() % ((mapSizeY / 2) - (mapSizeY / 5) + 1 - 1);
    int maxWallLength = mapSizeY / 2 + (mapSizeY / 4);
    int wallLength, posY, posX;
    Direction dir;
    std::cout << "nbrWall: " << nbrWall << std::endl;
    for (int i = 0; i < nbrWall; i++)
    {
        posY = rand() %(this->topOffest + 1  + (this->topOffest + mapSizeY));
        posX = rand() %(this->leftOffest  + (this->leftOffest + mapSizeX));  

        wallLength = (maxWallLength / 2) + rand() % (maxWallLength - (maxWallLength / 2) + 1 - 1);

        int x = 1 + rand() % 4; // Random direction
        switch (x)
        {
            case 1: dir = UP; break;
            case 2: dir = LEFT; break;
            case 3: dir = DOWN; break;
            case 4: dir = RIGHT; break;
            default: dir = UP; break;
        }
        std::cout << "posX: " << posX <<" ";
        std::cout << "posY: " << posY << std::endl;
        generateWall(posX, posY, dir, wallLength, mapSizeX, mapSizeY);
    }
}

void Map::generateWall(int posX, int posY, Direction dir, int length, int mapSizeX, int mapSizeY)
{
    bool breach = false;
    for (int i = 0; i < length; i++)
    {
        if (posX < this->leftOffest  || posX >= mapSizeX + this->leftOffest || posY < this->topOffest || posY >= mapSizeY + this->topOffest) break;

        grid[posX][posY] = WALL;

        if (dir == UP) {
            if (posX - 1 < (this->topOffest )) break;
            if (grid[posX - 1][posY] == GridElement::PATH) {
                breach = true;
                grid[posX - 1][posY] = GridElement::WALL;
                posX -= 1;
            }
            else {
                posX -= 1;
            }
        }
        else if (dir == DOWN) {
            if (posY + 1 >= mapSizeX + (this->topOffest )) break;
            if (grid[posX + 1][posY] == GridElement::PATH) {
                breach = true;
                grid[posX + 1][posY] = GridElement::WALL;
                posX += 1;
            }
            else {
                posX += 1;
            }
        }
        else if (dir == LEFT) {
            if (posY - 1 < (this->leftOffest )) break;
            if (grid[posX][posY - 1] == GridElement::PATH) {
                breach = true;
                grid[posX][posY - 1] = GridElement::WALL;
                posY -= 1;
            }
            else {
                posY -= 1;
            }
        }
        else if (dir == RIGHT) {
            if (posY + 1 >= mapSizeY + (this->leftOffest )) break;
            if (grid[posX][posY + 1] == GridElement::PATH) {
                breach = true;
                grid[posX][posY + 1] = WALL;
                posY += 1;
            }
            else {
                posY += 1;
            }
        }
        breach = false;
    }
}
