#include "Game.h"
#include "raylib.h"
#include "data.h"
#include <string>

const double MENU_STATE_DURATION = 5.0;
const double MENU2_STATE_DURATION = 2.0;

Game::Game(/* args */)
{
    srand(time(NULL));
    
    font = LoadFontEx("./font/monogram.tff", 64, 0, 0);
    
    menu = GetRandomValue(1,3) % 2 == 0 ? LoadTexture("./ressources/menu1.png") : LoadTexture("./ressources/menu2.png");
    
    start = new  Button("New Game", {250, 500}, {150, 60}, Data::tilesColors()[2], WHITE);
    start->setAction(std::bind(&Game::newGame, this));

    quit = new Button("Quit", {250, 600}, {150, 60}, Data::tilesColors()[2], WHITE);
    quit->setAction(std::bind(&Game::quitGame, this));
}

Game::~Game()
{
    UnloadTexture(menu);
    UnloadFont(font);
    delete start;
    delete quit;
    delete player;
    for(auto map : maps){
        delete map;
    }
}

void Game::display()
{
    if(!onGoing){
        drawMenu();
        return;
    }

    maps[currentMap]->drawMap2(*player);
    drawInfo();
}

void Game::handleInput()
{
    
   if(onGoing){
        int key = GetKeyPressed();
        if(key == KEY_LEFT_ALT){
        breakWall();
        }

        if(IsKeyDown(KEY_UP)){
        movePlayer(UP);
        player->updateRotation(0);
        }
        if(IsKeyDown(KEY_DOWN)){
            movePlayer(DOWN);
            player->updateRotation(180);
        }
        if(IsKeyDown(KEY_LEFT)){
            movePlayer(LEFT);
            player->updateRotation(270);
        }
        if(IsKeyDown(KEY_RIGHT)){
            movePlayer(RIGHT);
            player->updateRotation(90);
        }
   }
    
}

void Game::movePlayer(Direction dir)
{
    std::function<bool(int,int)> f = std::bind(&Game::teleport, this, std::placeholders::_1, std::placeholders::_2);
    maps[currentMap]->movePlayer(dir, *player, f, speed);
}

bool Game::breakWall()
{
    Direction dir;
    switch ((int)player->getRotation())
    {
    case 0:
        dir = UP;
        break;
    case 90:
        dir = RIGHT;
        break;
    case 180:
        dir = DOWN;
        break;
    case 270:
        dir = LEFT;
        break;
    default:
        return false;
    }
    return maps[currentMap]->breakWall(*player, dir, speed);
}

void Game::drawInfo()
{
    int textWidth = 0;
    int textX = 0;
    int textY = 0;

    DrawTextEx(font, "Level", {1060, 15}, 64, 2, WHITE);
    DrawTextEx(font, "Timer", {1060, 250}, 64, 2, WHITE);

    DrawRectangleRounded({1020, 100, 260, 60}, 0.3, 6, Data::tilesColors()[2]);
    DrawRectangleRounded({1020, 325, 260, 60}, 0.3, 6, Data::tilesColors()[2]);

    // Draw level number
    std::string s = std::to_string(currentMap);
    Vector2 textSize = MeasureTextEx(font, s.c_str(), 56, 2);
    textX = 1020 + (260 - textSize.x) / 2;  // Center text horizontally
    textY = 100 + (60 - textSize.y) / 2;    // Center text vertically
    DrawTextEx(font, s.c_str(), {(float)textX, (float)textY}, 56, 2, WHITE);

    // Draw remaining time
    int remainingTime = getRemainingTime();
    s = std::to_string(remainingTime);
    
    textSize = MeasureTextEx(font, s.c_str(), 56, 2);
    textX = 1020 + (260 - textSize.x) / 2;
    textY = 325 + (60 - textSize.y) / 2;

    Color textColor = (remainingTime > 10) ? WHITE : RED;
    DrawTextEx(font, s.c_str(), {(float)textX, (float)textY}, 56, 2, textColor);
}

void Game::drawMenu()
{
    
    DrawTexturePro(menu, {0, 0, (float)menu.width, (float)menu.height}, {0, 0, 1300, 1000}, {0, 0}, 0, WHITE);
    if(won){
         DrawTextEx(font,"You escaped just in time", {(float)150, (float)250}, 23, 2, RED);
         if((winMenuChrono - (int)(GetTime() - initialTime2)) < 0){
             won = false;
         }
    }
    else{
        if(gameOver){
            DrawTextEx(font,"GAME OVER", {(float)150, (float)250}, 56, 2, RED);
        }
        start->draw();
        quit->draw();
    }
    
}

void Game::newGame()
{
    std::cout << "Starting new game" << std::endl;
    player = new Player();

    numMaps = rand() % 12 + 3;
    unsigned int validMapsCount = 0;
    do{
        maps.clear();
        doorsList.clear();
        
        while (validMapsCount < numMaps) {
            int x = 50;//rand() % 48;
            int y = 50;rand() % 48;
            Map *map = new Map(x, y);
            if(map->getDoors().size() == 0){
                continue;
            }
            maps.push_back(map);
            for(auto door : map->getDoors()){
                Door d(door.first, door.second, validMapsCount);
                doorsList.push_back({validMapsCount, d});
            }
            validMapsCount++;
        }
        numMaps = maps.size();

        system("cls");
    }while (!linkMaps());
    
    
    currentMap = rand() % numMaps;
    maps[currentMap]->setPlayerPosition(playerPosition, *player);
    initialTime = GetTime();
    std::cout << "Current level " << currentMap << std::endl;
    startTime = GetTime();
    won = false;
    onGoing = true;
    pause = false;
    gameOver = false;

}

void Game::quitGame()
{
    std::cout << "Quitting game" << std::endl;
    CloseWindow();
}

void Game::win()
{
    std::cout << "You win" << std::endl;
    clean();
    won = true;
    onGoing = false;
    gameOver = false;
    initialTime2 = GetTime();
    std::cout << "Game Over" << std::endl;
}

int Game::getRemainingTime()
{
    return std::max(0, chrono - (int)(GetTime() - startTime)); // Prevent negative values
}

void Game::clean()
{
    for(auto map : maps){
        delete map;
    }
    maps.clear();
    doorsList.clear();
    delete player;
    playerPosition = {0, 0};
    escapedDoor = {0, Door()};
    doorsList.clear();
}

void Game::onGaming()
{
    if (onGoing){
        int remainingTime = getRemainingTime();
        if(remainingTime == 0){
            clean();
            onGoing = false;
            gameOver = true;
            std::cout << "Game Over" << std::endl;
        }
    }
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
    maps[currentMap]->setPlayerPosition(playerPosition, *player);
}

void Game::previousMap()
{
    currentMap = (currentMap - 1);
    maps[currentMap]->setPlayerPosition(playerPosition, *player);
}

bool Game::linkMaps()
{

    /* std::cout << "Linking maps" << std::endl;
    std::cout << "Total levels: " << numMaps << std::endl;

    // Step 1: Group doors by level
    std::cout << "Grouping doors by level" << std::endl; */
    std::map<int, std::vector<std::pair<int, Door>>> levelDoors;
    
    for (auto door : doorsList)
    {
        levelDoors[door.first].push_back(door);
    }

    // Step 2: Find levels with only one door
    //std::cout << "Finding levels with only one door" << std::endl;
    std::vector<int> singleDoorLevels;
    for (const auto& level : levelDoors)
    {
        if (level.second.size() == 1)
            singleDoorLevels.push_back(level.first);
    }

    //std::cout << "Levels with only one door: ";
    for (auto level : singleDoorLevels)
    {
        std::cout << level << " ";
    }
    std::cout << std::endl;

    if(singleDoorLevels.size() == numMaps){
        //std::cout << "All levels have only one door, cannot link maps" << std::endl;
        return false;
    }

    // Step 3: Shuffle doors and select escaped door
    //std::cout << "Shuffling doors and selecting escaped door" << std::endl;
    std::shuffle(doorsList.begin(), doorsList.end(), std::mt19937(std::random_device{}()));
    
    int rd;
    do {
        rd = rand() % doorsList.size();
    } while (std::find(singleDoorLevels.begin(), singleDoorLevels.end(), doorsList[rd].first) != singleDoorLevels.end());
    
    escapedDoor = doorsList[rd];
    doorsList[rd].second.setTo(-1);
    doorsList[rd].second.setDestination(-1, -1);
    /* std::cout << "door from level " 
    << escapedDoor.first 
    <<"[" << escapedDoor.second.getOriginX() << "," << escapedDoor.second.getOriginY() << "]" 
    << " is the escaped door"
    << std::endl; */

    // Step 4: Link doors across levels
    //std::cout << "Linking doors across levels" << std::endl;
    for ( int i = 0; i < doorsList.size(); i++)
    {
        if (i == rd || doorsList[i].second.hasDestination())
            continue;

        for ( int j = i + 1; j < doorsList.size(); j++)
        {
            if (j == rd || doorsList[j].second.hasDestination() || doorsList[i].first == doorsList[j].first)
                continue;

            // Check if both doors are from levels with only one door
            if(levelDoors[doorsList[i].first].size() == 1 && levelDoors[doorsList[j].first].size() == 1)
                continue;

            doorsList[i].second.setTo(doorsList[j].first);
            doorsList[i].second.setDestination(doorsList[j].second.getOriginX(), doorsList[j].second.getOriginY());
            doorsList[j].second.setTo(doorsList[i].first);
            doorsList[j].second.setDestination(doorsList[i].second.getOriginX(), doorsList[i].second.getOriginY());
            break; // Pair found, break inner loop
        }
    }

    // Step 5: Handle unlinked doors
    //std::cout << "Handling unlinked doors" << std::endl;
    std::vector<int> unlinkedDoors;  // To track unlinked doors

    for ( int i = 0; i < doorsList.size(); i++)
    {
        if (doorsList[i].second.hasDestination() || i == rd)
            continue;

        // Try cross-level linking first
        bool linked = false;
        for ( int j = 0; j < doorsList.size(); j++)
        {
            if (i == j || j == rd || doorsList[j].second.hasDestination())
                continue;

            if (doorsList[i].first != doorsList[j].first)  // Check if doors are from different levels
            {
                doorsList[i].second.setTo(doorsList[j].first);
                doorsList[i].second.setDestination(doorsList[j].second.getOriginX(), doorsList[j].second.getOriginY());
                doorsList[j].second.setTo(doorsList[i].first);
                doorsList[j].second.setDestination(doorsList[i].second.getOriginX(), doorsList[i].second.getOriginY());
                linked = true;
                break;
            }
        }

        // If no cross-level link found, try linking within the same level
        if (!linked)
        {
            for ( int j = 0; j < doorsList.size(); j++)
            {
                if (i == j || j == rd || doorsList[j].second.hasDestination())
                    continue;

                if (doorsList[i].first == doorsList[j].first)  // Check if doors are from the same level
                {
                    doorsList[i].second.setTo(doorsList[j].first);
                    doorsList[i].second.setDestination(doorsList[j].second.getOriginX(), doorsList[j].second.getOriginY());
                    doorsList[j].second.setTo(doorsList[i].first);
                    doorsList[j].second.setDestination(doorsList[i].second.getOriginX(), doorsList[i].second.getOriginY());
                    break; // Pair found, break inner loop
                }
            }
        }

        // If still not linked, track the unlinked door
        if (!doorsList[i].second.hasDestination())
        {
            unlinkedDoors.push_back(i);
        }
    }

    // Step 6: If there is exactly one unlinked door, link it randomly to another door
    //std::cout << "Linking unlinked doors" << std::endl;
    if (unlinkedDoors.size() == 1)
    {
        int unlinkedDoorIndex = unlinkedDoors[0];
        /* std::cout << "Linking unlinked door at level " 
        << doorsList[unlinkedDoorIndex].first 
        <<"[" << doorsList[unlinkedDoorIndex].second.getOriginX() << "," << doorsList[unlinkedDoorIndex].second.getOriginY() << "]"
        <<  " to level "
        << " randomly" << std::endl; */

        // Find another door to link to
        int randomDoorIndex;
        do {
            randomDoorIndex = rand() % doorsList.size();
        } while (randomDoorIndex == unlinkedDoorIndex );

        // Link the unlinked door to the randomly selected door
        doorsList[unlinkedDoorIndex].second.setTo(doorsList[randomDoorIndex].first);
        doorsList[unlinkedDoorIndex].second.setDestination(doorsList[randomDoorIndex].second.getOriginX(), doorsList[randomDoorIndex].second.getOriginY());


        // Make sure the link is one-way (no back-linking)
    }
/* 
    std::cout << std::endl;
    std::cout << "Final door connections:" << std::endl;
    for (auto& door : doorsList) {
        std::cout << "door from level " 
        << door.second.getFrom() 
        <<"[" << door.second.getOriginX() << "," << door.second.getOriginY() << "]"
        <<  " -> door to level " 
        << door.second.getTo() 
        <<"[" << door.second.getDestinationX() << "," << door.second.getDestinationY() << "]"
         << std::endl;
    }
    std::cout << "Linking maps process finished" << std::endl; */
    return true;
}

bool Game::teleport(int x, int y)
{
    // check if the player is in the escaped door
    if (currentMap == escapedDoor.first && x == escapedDoor.second.getOriginX() && y == escapedDoor.second.getOriginY())
    {
        //thee player is in the escaped door
        std::cout << "Player is in the escaped door" << std::endl;
        win();
        return false;
    }
    else{
        // teleport the player to the corresponding door
        for (auto door : doorsList)
        {
            if (door.first == currentMap && door.second.getFrom() == currentMap && door.second.getOriginX() == x && door.second.getOriginY() == y)
            {
                currentMap = door.second.getTo();
                if(!maps[currentMap]->openDoor(door.second.getDestinationX(), door.second.getDestinationY(), *player)){
                    std::cout << "Door in the destination map is closed" << std::endl;
                    return false;
                }else{
                    std::cout << "Teleporting player to level " << currentMap << std::endl;
                    return true;
                }
                break;
            }
        }
    }
    std::cout << "Can not teleporting player to another level" << std::endl;
    return false;
}


