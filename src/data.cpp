#include "data.h"

// Define the texture file paths in one cpp file
const char* Data::TILE_TEXTURE_PATH = "./ressources/tiles.png";
const char* Data::PLAYER_TEXTURE_PATH = "./ressources/character/doctor.png";
const Texture2D Data::tilesTexture = LoadTexture(Data::TILE_TEXTURE_PATH);
const Texture2D Data::playerTexture = LoadTexture(Data::PLAYER_TEXTURE_PATH);
