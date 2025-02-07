#include "raylib.h"
#include "game.h"

int main(int argc, char* argv[])
{
    srand(static_cast<unsigned int>(time(NULL)));
    Color lightgray = { 200, 200, 200, 255 };

    const int screenWidth = 1300;
    const int screenHeight = 1000;
    // Initialize window
    InitWindow(screenWidth, screenHeight, "Hotel Escape");
    SetTargetFPS(60);
    Game game;
    //bool showMap = true;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        {
            ClearBackground(lightgray);
            game.onGaming();
            game.handleInput();
            game.display();
        }

        EndDrawing();
    }


    CloseWindow();

    return 0;
}