#include "Game.h"

#include "raylib.h"

Game::Game(/* args */)
{
    srand(time(NULL));

    numMaps = rand() % 15 + 1;

    for (unsigned int i = 0; i < numMaps; i++){
        int x = rand() % 48;
        int y = rand() % 48;
        Map map(x, y);
        maps.push_back(map);
    }
    currentMap = 0;
    maps[currentMap].setPlayerPosition();
    
}

Game::~Game()
{
}

void Game::display()
{
    maps[currentMap].drawMap();
}
void Game::handleInput()
{
    int keyPressed = GetKeyPressed();

    switch (keyPressed)
    {
    case KEY_LEFT:
        movePlayer(LEFT);
        break;
    case KEY_RIGHT:
        movePlayer(RIGHT);
        break;
    case KEY_UP:
        movePlayer(UP);
        break;
    case KEY_DOWN:
        movePlayer(DOWN);
        break;
    case KEY_B:
        breakWall();
        break;
    default:
        break;
    }
}

void Game::movePlayer(Direction dir)
{
    
}

void Game::breakWall()
{
}

int Game::getNumMaps()
{
    return this->numMaps;
}

int Game::getCurrentMap()
{
    return this->currentMap;
}

void Game::nextMap()
{
    currentMap = (currentMap + 1) ;
    maps[currentMap].setPlayerPosition();
}

void Game::previousMap()
{
    currentMap = (currentMap - 1);
    maps[currentMap].setPlayerPosition();
}