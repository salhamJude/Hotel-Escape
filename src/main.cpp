#include "raylib.h"
#include "game.h"
int main(int argc, char* argv[])
{
    srand(static_cast<unsigned int>(time(NULL)));
    Color lightgray = { 200, 200, 200, 255 };

    const int screenWidth = 1000;
    const int screenHeight = 1000;

    Game game;

    // Initialize window
    InitWindow(screenWidth, screenHeight, "Hotel Escape");
    SetTargetFPS(60);

    bool showMap = true;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        {
            ClearBackground(lightgray);
            game.display();
            game.handleInput();
        }

        EndDrawing();
    }


    CloseWindow();

    return 0;
}