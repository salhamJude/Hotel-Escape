#include "raylib.h"

int main()
{
    Color darkGreen = Color{20, 160, 133, 255};

    const int screenWidth = 800;
    const int screenHeight = 600;


    InitWindow(screenWidth, screenHeight, "Hotel Escape");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(darkGreen);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}