#include "Player.h"
#include "raylib.h"

Player::Player()
{
    playerTextures = Data::playerTextures();
    rotation = 0.0f;
}

void Player::draw(int x, int y, int tileSize) const
{
    
    std::pair<Texture2D, Rectangle> texture = playerTextures[currentTexture];
    Rectangle dest = {0, 0, (float)tileSize, (float)tileSize};

    dest.x = (y * tileSize);
    dest.y = (x * tileSize);

    DrawTexturePro(texture.first,texture.second,dest,(Vector2){0, 0},0,WHITE);
}

void Player::updateRotation(float rotation)
{
    this->rotation = rotation;
    if(rotation > 360.0f)
    {
        rotation = 0.0f;
    }

    if(rotation > 315 || rotation <= 45)
    {
        currentTexture = 1;
    }
    else if(rotation > 45 && rotation <= 135)
    {
        currentTexture = 0;
    }
    else if(rotation > 135 && rotation <= 225)
    {
        currentTexture = 3;
    }
    else if(rotation > 225 && rotation <= 315)
    {
        currentTexture = 2;
    }
}
