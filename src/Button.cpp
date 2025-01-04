#include "Button.h"

Button::Button(std::string text, Vector2 position, Vector2 size, Color color, Color textColor)
{
    this->text = text;
    this->position = position;
    this->size = size;
    this->color = color;
    this->textColor = textColor;
    this->isHovered = false;
    this->isClicked = false;
    draw(); 
}

Button::~Button()
{

}

void Button::draw()
{
    isHovered = CheckCollisionPointRec(GetMousePosition(), {position.x, position.y, size.x, size.y});
    Rectangle rec = {position.x, position.y, size.x, size.y};
    if(isHovered){
        DrawRectangleRounded(rec, 2, 0.3, GRAY);
    }else{
        DrawRectangleRounded(rec, 2, 0.3, color);
    }
    DrawText(text.c_str(), position.x + (size.x * 0.2), position.y + (size.y * 0.3), 20, textColor);
}
