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
        isClicked = false;
    }

    int textWidth = MeasureText(text.c_str(), 20);
    int textX = position.x + (size.x - textWidth) / 2;
    int textY = position.y + (size.y - 20) / 2;
    DrawText(text.c_str(), textX, textY, 20, textColor);

    this->handleClick();
}

void Button::setAction(std::function<void()> action)
{
    if(!actionset){
        this->action = action;
        actionset = true;
    }
}

void Button::handleClick()
{
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        if(isHovered && !isClicked){
            isClicked = true;
            if(actionset){
                this->action();
            }else{
                std::cout << "Action not set" << std::endl;
            }
        }
    }

    if(IsMouseButtonUp(MOUSE_BUTTON_LEFT)){
        isClicked = false;
    }
    
}
