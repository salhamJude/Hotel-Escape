#ifndef BUTTON_H
#define BUTTON_H

#include "raylib.h"
#include <string>
#include <iostream>
#include <functional>

class Button{

public:
    Button(std::string text, Vector2 position, Vector2 size, Color color, Color textColor );
    ~Button();
    void draw();
    void setAction(std::function<void()> action);

private:
    void handleClick();
    std::string text;
    Vector2 position;
    Vector2 size;
    Color color;
    Color textColor;
    bool isHovered;
    bool isClicked; 
    bool actionset = false;
    std::function<void()> action;

};

#endif //BUTTON_H