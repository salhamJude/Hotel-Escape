#ifndef PLAYER_H
#define PLAYER_H

#include "data.h"
class Player
{
public:
    Player();
    ~Player();
    void draw(int x, int y, int tileSize) const;
    void draw(int tileSize) const;
    void updateRotation(float rotation);
    void updatePosition(int x, int y, int tileSize);
    std::pair<int, int> getPosition();
    float getRotation() const;
    
private:
    std::vector<std::pair<Texture2D, Rectangle>> playerTextures;
    std::vector<std::pair<Texture2D, Rectangle>> getPlayerTextures();
    int currentTexture = 0;
    float rotation = 0.0f;
    bool isMoving = false;
    std::pair<int, int> position;
    Texture2D texture;
};

#endif // PLAYER_H