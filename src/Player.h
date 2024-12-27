#ifndef PLAYER_H
#define PLAYER_H

#include "data.h"
class Player
{
public:
    Player();
    void draw(int x, int y, int tileSize) const;
    void updateRotation(float rotation);
    
private:
    std::vector<std::pair<Texture2D, Rectangle>> playerTextures;
    int currentTexture = 0;
    float rotation = 0.0f;
    bool isMoving = false;
};

#endif // PLAYER_H