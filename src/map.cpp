#include "Map.h"
#include "raylib.h"

Map::Map(int x, int y)
{
    if(x >= mapMaxSizeX - 1 || y >= mapMaxSizeY - 1)
    {
        x = mapMaxSizeX - 2;
        y = mapMaxSizeY - 2;
    }

    mapSizeX = x;
    mapSizeY = y;

    topOffest = 0;
    leftOffest = 0;

    for (int i = 0; i < mapMaxSizeX; i++)
    {
       for (int j = 0; j < mapMaxSizeY; j++)
       {
              grid[i][j] = GridElement::EMPTY;
       }
       
    }

    if(mapSizeX < mapMaxSizeX){
        topOffest = round((mapMaxSizeX - mapSizeX) / 2);
    }

    if(mapSizeY < mapMaxSizeY){
        leftOffest = round((mapMaxSizeY - mapSizeY) / 2);
    }

    //std::cout << "topOffest: " << topOffest << std::endl;
    //std::cout << "leftOffest: " << leftOffest << std::endl;
    for (int i = 0; i < mapMaxSizeX; i++)
    {
       for (int j = 0; j < mapMaxSizeY; j++)
       {
            if((i >= topOffest && i < mapSizeX + topOffest) && (j >= leftOffest && j < mapSizeY + leftOffest)){
                grid[i][j] = GridElement::PATH;
            }
       }
    }
    tilesColors = Data::tilesColors();
    tilesTextures = Data::tilesTextures();
    generateMapElements();
}

Map::Map()
{
    mapSizeX = rand() % 48;
    mapSizeY = rand() % 48;

    topOffest = 0;
    leftOffest = 0;

    for (int i = 0; i < mapMaxSizeX; i++)
    {
       for (int j = 0; j < mapMaxSizeY; j++)
       {
              grid[i][j] = GridElement::EMPTY;
       }
       
    }

    if(mapSizeX < mapMaxSizeX){
        topOffest = round((mapMaxSizeX - mapSizeX) / 2);
    }

    if(mapSizeY < mapMaxSizeY){
        leftOffest = round((mapMaxSizeY - mapSizeY) / 2);
    }

    std::cout << "topOffest: " << topOffest << std::endl;
    std::cout << "leftOffest: " << leftOffest << std::endl;
    for (int i = 0; i < mapMaxSizeX; i++)
    {
       for (int j = 0; j < mapMaxSizeY; j++)
       {
            if((i >= topOffest && i < mapSizeX + topOffest) && (j >= leftOffest && j < mapSizeY + leftOffest)){
                grid[i][j] = GridElement::PATH;
            }
       }
    }
    tilesColors = Data::tilesColors();
    tilesTextures = Data::tilesTextures();
    generateMapElements();
}

Map& Map::operator=(const Map& other)
{
    // Check for self-assignment
    if (this == &other) {
        return *this;  // Return the current object to handle the case of self-assignment
    }

    // Copy the simple data members
    mapSizeX = other.mapSizeX;
    mapSizeY = other.mapSizeY;
    topOffest = other.topOffest;
    leftOffest = other.leftOffest;
    
    // Copy the grid elements
    for (int i = 0; i < mapMaxSizeX; i++) {
        for (int j = 0; j < mapMaxSizeY; j++) {
            grid[i][j] = other.grid[i][j];
        }
    }

    // Copy the tiles colors and textures
    tilesColors = other.tilesColors;
    tilesTextures = other.tilesTextures;

    // Re-generate map elements (optional, depending on whether you want the elements recalculated on assignment)
    generateMapElements();

    // Return the current object to allow chained assignment (a = b = c)
    return *this;
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
            case GridElement::COUNTOURED_WALL:
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
            case GridElement::VISITED:
                clr = tilesColors[6];
                break;
            default:
                break;
            }

            if(grid[row][column] == GridElement::EMPTY){
                DrawRectangle(column * tileSize, row * tileSize, tileSize, tileSize, clr);
            }else{
                DrawRectangle(column * tileSize + 1, row * tileSize + 1, tileSize - 1, tileSize - 1, clr);
            }
       }
       
    }

}

void Map::drawMap2(const Player& player)
{
    std::pair<Texture2D, Rectangle> texture;

    
    Rectangle dest = {0, 0, tileSize, tileSize};
    float scaleFactor = 0.98f;
    float scaledSize = tileSize * scaleFactor;
    float gapOffset = (tileSize - scaledSize) / 2.0f;

    for (int row = 0; row < mapMaxSizeX; row++)
    {
       for (int column = 0; column < mapMaxSizeY; column++)
       {
            switch (grid[row][column])
            {
            case GridElement::EMPTY:
                texture = tilesTextures[4];
                break;
            case GridElement::WALL:
                texture = tilesTextures[2];
                break;
            case GridElement::COUNTOURED_WALL:
                texture = tilesTextures[5];
                break;
            case GridElement::PLAYER:
                texture = tilesTextures[0];
                break;
            case GridElement::DOOR:
                texture = tilesTextures[1];
                break;
            case GridElement::PATH:
                texture = tilesTextures[0];
                break;
            case GridElement::VISITED:
                texture = tilesTextures[0];
                break;
            default:
                break;
            }

            if(grid[row][column] != GridElement::COUNTOURED_WALL && grid[row][column] != GridElement::EMPTY){
                dest = {
                        column * tileSize + gapOffset,
                        row * tileSize + gapOffset,
                        scaledSize,
                        scaledSize
                    };
            }else{
                dest = {0, 0, (float)tileSize, (float)tileSize};
                dest.x = (column * tileSize);
                dest.y = (row * tileSize);
            }
            DrawTexturePro(texture.first,texture.second,dest,(Vector2){0, 0},0.0f,WHITE);

            if(grid[row][column] == GridElement::PLAYER){
                player.draw(row, column, tileSize);
            }   

       }
       
    }
}

void Map::generateMapElements()
{
    this->generateCountourWalls();
    this->generateWalls();
    this->generateDoors();
}

void Map::generateWalls()
{
    
    int nbrWall = (mapSizeX * mapSizeY) / 60 + rand() % ((mapSizeX * mapSizeY) / 40 - (mapSizeX * mapSizeY) / 100 + 1);
    int maxWallLength = mapSizeY / 2 + (mapSizeY / 4);
    int wallLength, posY, posX;
    Direction dir;
    //std::cout << "nbrWall: " << nbrWall << std::endl;
    for (int i = 0; i < nbrWall; i++)
    {
        posY = rand() % (this->leftOffest + 1 + (this->leftOffest + mapSizeY));
        posX = rand() % (this->topOffest + (this->topOffest + mapSizeX));  

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
        //std::cout << "posX: " << posX <<" ";
        //std::cout << "posY: " << posY << std::endl;
        generateWall(posX, posY, dir, wallLength, mapSizeX, mapSizeY);
    }
}

void Map::generateWall(int posX, int posY, Direction dir, int length, int mapSizeX, int mapSizeY)
{
    bool breach = false;
    for (int i = 0; i < length; i++)
    {
        if (posX < this->topOffest || posX >= mapSizeX + this->topOffest || posY < this->leftOffest || posY >= mapSizeY + this->leftOffest) break;

        grid[posX][posY] = WALL;

        if (dir == UP) {
            if (posX - 1 < (this->topOffest)) break;
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
            if (posY + 1 >= mapSizeX + (this->topOffest)) break;
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
            if (posY - 1 < (this->leftOffest)) break;
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
            if (posY + 1 >= mapSizeY + (this->leftOffest)) break;
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

void Map::generateCountourWalls()
{
    for (int i = 0; i < mapMaxSizeX; i++)
    {
        for (int j = 0; j < mapMaxSizeY; j++)
        {
            if(i >= topOffest -1 && i < mapSizeX + topOffest + 1 && j >= leftOffest -1 && j < mapSizeY + leftOffest + 1){
                if((i == topOffest-1 || i == mapSizeX + topOffest) || (j == leftOffest-1 || j == mapSizeY + leftOffest)){
                    grid[i][j] = GridElement::COUNTOURED_WALL;
                }
            }
            
        }
    }
}

void Map::floodFill(int x, int y, std::vector<std::pair<int, int>>& enclosedArea) {
    
    int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    std::queue<std::pair<int, int>> q;
    q.push({x, y});
    grid[x][y] = GridElement::VISITED; // Mark as visited
    enclosedArea.push_back({x, y});

    while (!q.empty()) {
        auto [cx, cy] = q.front();
        q.pop();
        for (auto& dir : directions) {
            int nx = cx + dir[0], ny = cy + dir[1];
            if (nx >= topOffest && nx <= mapSizeX + topOffest && ny >= leftOffest && ny <= mapSizeY + leftOffest) {
                //std::cout << "nx: " << nx << " ny: " << ny << std::endl;
                if(grid[nx][ny] == GridElement::PATH){
                    grid[nx][ny] = GridElement::VISITED; // Mark as visited
                    q.push({nx, ny});
                    enclosedArea.push_back({nx, ny});
                }
            }
        }
    }
}

bool Map::isEnclosed(const std::vector<std::pair<int, int>>& enclosedArea) {
    //std::cout << "Enclosed area: " ;
    for (auto& cell : enclosedArea) {
        int x = cell.first, y = cell.second;
        if (x == topOffest-1  || x == mapSizeX + topOffest   || y == leftOffest-1   || y == mapSizeY + leftOffest  ) {
            //std::cout << "opened: " << std::endl;
            return false; // Not enclosed if it touches the boundary
        }
    }
    std::cout << "closed: " << std::endl;
    return true;
}

void Map::placeDoor(const std::vector<std::pair<int, int>>& enclosedArea) {
    for (const auto& cell : enclosedArea) {
        for (const auto& dir : std::vector<std::pair<int, int>>{{0, 1}, {1, 0}, {0, -1}, {-1, 0}}) {
            int nx = cell.first + dir.first, ny = cell.second + dir.second;
            if (grid[nx][ny] == GridElement::WALL) {
                // Check if the door would be between two spaces
                int oppositeX = nx - dir.first;
                int oppositeY = ny - dir.second;
                if (grid[oppositeX][oppositeY] != GridElement::PATH) {
                    grid[nx][ny] = GridElement::DOOR;
                    doors.push_back({nx, ny});
                    //std::cout << "placeDoor at "<<nx << " " << ny << std::endl;
                    return;
                }
            }
        }
    }
}

void Map::setPlayerPosition(std::pair<int, int>& playerPosition)
{
    int set = false;
    do
    {
        int x = rand() % mapSizeX + topOffest;
        int y = rand() % mapSizeY + leftOffest;

        if(grid[x][y] == GridElement::PATH){
            set = true;
            grid[x][y] = GridElement::PLAYER;
            playerPosition.first = x;
            playerPosition.second = y;
        }

    } while (!set);
    
}

void Map::detectAndFixEnclosedSpaces() {
    for (int x = topOffest ; x < mapSizeX + topOffest; ++x) {
        for (int y = leftOffest ; y < mapSizeY + leftOffest; ++y) {
            //std::cout << "Checking: " << x << " " << y << std::endl;
            if (grid[x][y] == GridElement::PATH) {
                std::vector<std::pair<int, int>> enclosedArea;
                floodFill(x, y, enclosedArea);
                if (isEnclosed(enclosedArea)) {
                    placeDoor(enclosedArea);
                }
                break;
            }
        }
    }

    // Reset visited spaces back to PATH
    for (int x = topOffest ; x < mapSizeX + topOffest; ++x) {
        for (int y = leftOffest; y < mapSizeY + leftOffest; ++y) {
            if (grid[x][y] == GridElement::VISITED) {
                //std::cout << "Resetting: " << x << " " << y << std::endl;
                grid[x][y] = GridElement::PATH;
            }
        }
    }
}

void Map::move(int x, int y, std::pair<int, int>& playerPosition)
{
    int px = playerPosition.first;
    int py = playerPosition.second;

    grid[px][py] = GridElement::PATH;
    grid[px + x][py + y] = GridElement::PLAYER;
    playerPosition.first = px + x;
    playerPosition.second = py + y;
}

void Map::teleport(int x, int y, std::pair<int, int> &playerPosition, std::function<bool(int,int)> teleportCallBack)
{
    int px = playerPosition.first;
    int py = playerPosition.second;

    if(teleportCallBack(px + x, py + y)){
        std::cout << "Teleporting player" << std::endl;
        grid[px][py] = GridElement::PATH;
    }else{
        std::cout << "Door is closed" << std::endl;
    }
}

void Map::generateDoors() {
    detectAndFixEnclosedSpaces();
}

void Map::movePlayer(Direction dir, std::pair<int, int>& playerPosition, std::function<bool(int,int)> teleportCallBack){
    int x = playerPosition.first;
    int y = playerPosition.second;
    if(grid[x][y] != GridElement::PLAYER){
        std::cout << "Player not found" << std::endl;
        return;
    }



    if(dir == UP){
        if(grid[x - 1][y] == GridElement::PATH){
            move(-1, 0, playerPosition);
        }else if(grid[x - 1][y] == GridElement::DOOR){
            teleport(-1, 0, playerPosition, teleportCallBack);
        }
    }else if(dir == DOWN){
        if(grid[x + 1][y] == GridElement::PATH){
            move(1, 0, playerPosition);
        }else if(grid[x + 1][y] == GridElement::DOOR){
            teleport(1, 0, playerPosition, teleportCallBack);
        }
    }else if(dir == LEFT){
        if(grid[x][y - 1] == GridElement::PATH){
            move(0, -1, playerPosition);
        }else if(grid[x][y - 1] == GridElement::DOOR){
            teleport(0, -1, playerPosition, teleportCallBack);
        }
    }else if(dir == RIGHT){
        if(grid[x][y + 1] == GridElement::PATH){
            move(0, 1, playerPosition);
        }else if(grid[x][y + 1] == GridElement::DOOR){
            teleport(0, +1, playerPosition, teleportCallBack);
        }
    }   
}

void Map::removeDoor(int x, int y)
{
    if(grid[x][y] == GridElement::DOOR){
        grid[x][y] = GridElement::PATH;
        std::cout << "Door removed" << std::endl;
    }
}

std::vector<std::pair<int, int>> Map::getDoors()
{
    return doors;
}

bool Map::openDoor(int x, int y, std::pair<int, int> &playerPosition)
{
    if(grid[x][y] == GridElement::DOOR){
        if(grid[x + 1 ][y] == GridElement::PATH){
            grid[x+ 1][y] = GridElement::PLAYER;
            playerPosition.first = x + 1;
            playerPosition.second = y;
            return true;
        }else if(grid[x - 1 ][y] == GridElement::PATH){
            grid[x - 1][y] = GridElement::PLAYER;
            playerPosition.first = x - 1;
            playerPosition.second = y;
            return true;
        }else if(grid[x][y + 1] == GridElement::PATH){
            grid[x][y + 1] = GridElement::PLAYER;
            playerPosition.first = x;
            playerPosition.second = y + 1;
            return true;
        }else if(grid[x][y - 1] == GridElement::PATH){
            grid[x][y - 1] = GridElement::PLAYER;
            playerPosition.first = x;
            playerPosition.second = y - 1;
            return true;
        }
    }
    return false;
}
