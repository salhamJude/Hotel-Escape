#include "raylib.h"
#include <string>


class Button{

public:
    Button(std::string text, Vector2 position, Vector2 size, Color color, Color textColor );
    ~Button();

private:
    void draw();
    std::string text;
    Vector2 position;
    Vector2 size;
    Color color;
    Color textColor;
    bool isHovered;
    bool isClicked; 

};