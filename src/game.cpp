#include "Game.h"



Game::Game(/* args */)
{
    srand(time(NULL));

    numMaps = rand() % 12 + 3;
    do{
        maps.clear();
        doorsList.clear();
        
        for (unsigned int i = 0; i < numMaps; i++){
            int x = rand() % 48;
            int y = rand() % 48;
            Map map(x, y);
            maps.push_back(map);
            for(auto door : map.getDoors()){
                Door d(door.first, door.second, i);
                doorsList.push_back({i, d});
            }
        }
        currentMap = 0;
        maps[currentMap].setPlayerPosition(playerPosition);
        system("cls");
    }while (!linkMaps());
    

    initialTime = GetTime();
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
    double elapsedTime = GetTime() - initialTime;
    std::cout << "Elapsed time: " << elapsedTime << std::endl;
    if(elapsedTime < speed){
        return;
    }
    if(IsKeyDown(KEY_UP)){
        movePlayer(UP);
        initialTime = GetTime();
    }
    if(IsKeyDown(KEY_DOWN)){
        movePlayer(DOWN);
        initialTime = GetTime();
    }
    if(IsKeyDown(KEY_LEFT)){
        movePlayer(LEFT);
        initialTime = GetTime();
    }
    if(IsKeyDown(KEY_RIGHT)){
        movePlayer(RIGHT);
        initialTime = GetTime();
    }
   /*  int keyPressed = GetKeyPressed();

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
    } */
}

void Game::movePlayer(Direction dir)
{
    std::cout << "Moving player" << std::endl;
    maps[currentMap].movePlayer(dir, playerPosition);
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
    maps[currentMap].setPlayerPosition(playerPosition);
}

void Game::previousMap()
{
    currentMap = (currentMap - 1);
    maps[currentMap].setPlayerPosition(playerPosition);
}

bool Game::linkMaps()
{
    std::cout << "Linking maps" << std::endl;
    std::cout << "Total levels: " << numMaps << std::endl;

    // Step 1: Group doors by level
    std::cout << "Grouping doors by level" << std::endl;
    std::map<int, std::vector<std::pair<int, Door>>> levelDoors;
    for (auto door : doorsList)
    {
        levelDoors[door.first].push_back(door);
    }

    // Step 2: Find levels with only one door
    std::cout << "Finding levels with only one door" << std::endl;
    std::vector<int> singleDoorLevels;
    for (const auto& level : levelDoors)
    {
        if (level.second.size() == 1)
            singleDoorLevels.push_back(level.first);
    }
    std::cout << "Levels with only one door: ";
    for (auto level : singleDoorLevels)
    {
        std::cout << level << " ";
    }
    std::cout << std::endl;
    if(singleDoorLevels.size() == numMaps){
        std::cout << "All levels have only one door, cannot link maps" << std::endl;
        return false;
    }
    // Step 3: Shuffle doors and select escaped door
    std::cout << "Shuffling doors and selecting escaped door" << std::endl;
    std::shuffle(doorsList.begin(), doorsList.end(), std::mt19937(std::random_device{}()));
    
    int rd;
    do {
        rd = rand() % doorsList.size();
    } while (std::find(singleDoorLevels.begin(), singleDoorLevels.end(), doorsList[rd].first) != singleDoorLevels.end());
    
    escapedDoor = doorsList[rd];
    doorsList[rd].second.setTo(-1);
    doorsList[rd].second.setDestination(-1, -1);
    std::cout << "door from level " 
    << escapedDoor.first 
    <<"[" << escapedDoor.second.getOriginX() << "," << escapedDoor.second.getOriginY() << "]" 
    << " is the escaped door"
    << std::endl;

    // Step 4: Link doors across levels
    std::cout << "Linking doors across levels" << std::endl;
    for ( int i = 0; i < doorsList.size(); i++)
    {
        if (i == rd || doorsList[i].second.hasDestination())
            continue;

        for ( int j = i + 1; j < doorsList.size(); j++)
        {
            if (j == rd || doorsList[j].second.hasDestination() || doorsList[i].first == doorsList[j].first)
                continue;

            doorsList[i].second.setTo(doorsList[j].first);
            doorsList[i].second.setDestination(doorsList[j].second.getOriginX(), doorsList[j].second.getOriginY());
            doorsList[j].second.setTo(doorsList[i].first);
            doorsList[j].second.setDestination(doorsList[i].second.getOriginX(), doorsList[i].second.getOriginY());
            break; // Pair found, break inner loop
        }
    }

    // Step 5: Handle unlinked doors
    std::cout << "Handling unlinked doors" << std::endl;
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
    std::cout << "Linking unlinked doors" << std::endl;
    if (unlinkedDoors.size() == 1)
    {
        int unlinkedDoorIndex = unlinkedDoors[0];
        std::cout << "Linking unlinked door at level " 
        << doorsList[unlinkedDoorIndex].first 
        <<"[" << doorsList[unlinkedDoorIndex].second.getOriginX() << "," << doorsList[unlinkedDoorIndex].second.getOriginY() << "]"
        <<  " to level "
        << " randomly" << std::endl;

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

    std::cout << std::endl;
    std::cout << "Final door connections:" << std::endl;
    for (auto& door : doorsList) {
        std::cout << "door from level " 
        << door.first 
        <<"[" << door.second.getOriginX() << "," << door.second.getOriginY() << "]"
        <<  " -> door to level " 
        << door.second.getTo() 
        <<"[" << door.second.getDestinationX() << "," << door.second.getDestinationY() << "]"
         << std::endl;
    }
    std::cout << "Linking maps process finished" << std::endl;
    return true;
}


