#include "raylib.h"
#include "map.h"

int main()
{
    srand(time(NULL));
    Color lightgray = Color{ 200, 200, 200, 255 };

    const int screenWidth = 1000;
    const int screenHeight = 1000;

    Map map(45, 40);
    InitWindow(screenWidth, screenHeight, "Hotel Escape");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(lightgray);
        map.drawMap();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}