#ifndef DATA_H
#define DATA_H

#include <vector>
#include "raylib.h"

namespace Data {
    inline std::vector<Color> tilesColors () {

        Color black = {0, 0, 0, 255};
        Color white = {255, 255, 255, 255};
        Color orange = { 255, 161, 0, 255 };
        Color red  = { 230, 41, 55, 255 };
        Color green = { 0, 228, 48, 255 };
        Color blue = { 102, 191, 255, 255 };

        return {black, white, orange, red, green, blue};
    };
} // namespace Data

#endif // DATA_H