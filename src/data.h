#ifndef DATA_H
#define DATA_H

#include <vector>
#include <utility>
#include "raylib.h"

namespace Data {
    
    inline std::vector<Color> tilesColors () {

        Color black = {0, 0, 0, 255};
        Color white = {255, 255, 255, 255};
        Color orange = { 255, 161, 0, 255 };
        Color red  = { 230, 41, 55, 255 };
        Color green = { 0, 228, 48, 255 };
        Color blue = { 102, 191, 255, 255 };
        Color Pink = { 255, 109, 194, 255 };
        return {black, white, orange, red, green, blue, Pink};
    };

    inline std::vector<std::pair<Texture2D, Rectangle>> tilesTextures() {

        Texture2D texture = LoadTexture("./ressources/tiles.png");
        std::vector<std::pair<Texture2D, Rectangle>> tiles;

        //tile 1 for path
        Rectangle rec = {240, 48, 48, 48};
        tiles.push_back({texture, rec});

        //tile 29 for door
        rec = {192, 144, 48, 48};
        tiles.push_back({texture, rec});

        //tile 18 for wall
        rec = {48, 96, 48, 48};
        tiles.push_back({texture, rec});

        //tile 8
        rec = {144, 96, 48, 48};
        tiles.push_back({texture, rec});

        //tile 20 for empty
        rec = {144, 96, 48, 48};
        tiles.push_back({texture, rec});

        //tile 19 for contoured wall
        rec = {96, 96, 48, 48};
        tiles.push_back({texture, rec});
        return tiles;

    }
    inline std::vector<std::pair<Texture2D, Rectangle>> playerTextures() {
        std::vector<std::pair<Texture2D, Rectangle>> players;

        //going east
        Texture2D texture = LoadTexture("./ressources/character/doctor.png");
        Rectangle rec = {48, 96, 48, 48};
        players.push_back({texture, rec});

        //going north
        //texture = LoadTexture("./ressources/character/C_Walk_NORTH_strip4.png");
        rec = {48, 144, 48, 48};
        players.push_back({texture, rec});

        //going west
        //texture = LoadTexture("./ressources/character/C_Walk_WEST_strip4.png");
        rec = {48, 48, 48, 48};
        players.push_back({texture, rec});

        //going south
        //texture = LoadTexture("./ressources/character/C_Walk_SOUTH_strip4.png");
        rec = {48, 0, 48, 48};
        players.push_back({texture, rec});

        return players;
    }
} // namespace Data

#endif // DATA_H